//
// Created by Pavel Filonov on 23.05.15.
//

#include "IniParser.h"

#include "Logging.h"

#include <string>
#include <sstream>
#include <stdexcept>

static auto &logger = Logger::getLogger("IniParser");

namespace {
    struct Token {
        enum class Type {
            Newline,
            Lbracket,
            Rbracket,
            String,
            Assign,
            Eof,
            Unknown,
        };

        Token(Type type_, const std::string &value_ = std::string())
                : type{type_}, value{value_} { }

        Type type;
        std::string value;
    };

    class Lexer {
    public:
        Lexer(std::istream &stream)
                : stream_{stream} { }

        Token nextToken() {
            int ch;
            // skip spaces and tabulars
            do {
                ch = nextChar();
            } while (ch != Eof && (ch == ' ' || ch == '\t'));


            // skip comment lines which starts with semicolon or #
            if (ch == '#' || ch == ';') {
                do {
                    ch = nextChar();
                } while (ch != Eof && ch != '\n');
                // rollback on one char
            }
            if (ch == Eof) {
                return Token(Token::Type::Eof);
            }
            if (ch == '\n') {
                ++line_;
                col_ = 0;
                return Token(Token::Type::Newline);
            }
            if (ch == '[') {
                return Token(Token::Type::Lbracket);
            }
            if (ch == ']') {
                return Token(Token::Type::Rbracket);
            }
            if (ch == '=') {
                return Token(Token::Type::Assign);
            }
            // TODO: add quoted strings
            if (isalnum(ch)) {
                std::string value;
                do {
                    value += ch;
                    ch = nextChar();
                } while (ch != Eof && !(isspace(ch) || ch == '=' || ch == ']' || ch == ';' || ch == '#'));
                if (ch != Eof) {
                    // if not eof place last char back to stream
                    stream_.unget();
                }
                return Token(Token::Type::String, value);
            }
            return Token(Token::Type::Unknown, std::string(ch, 1));
        }

        std::string error_msg(const std::string &msg) const {
            std::stringstream ss;
            ss << "IniParserError:" << line_ << ":" << col_ << ": " << msg;
            return ss.str();
        }

    private:
        int nextChar() {
            char ch;
            if (stream_ >> ch) ++col_;
            LOG_TRACE(logger, "nextChar: " << ch);
            return stream_ ? ch : Eof;
        }
        static const int Eof = -1;
        size_t line_ = 1;
        size_t col_ = 0;
        std::istream &stream_;
    };

    std::ostream &operator<<(std::ostream &stream, const Token &token) {
        switch (token.type) {
            case Token::Type::Newline:
                stream << "NewLine";
                break;
            case Token::Type::Lbracket:
                stream << "Lbracket";
                break;
            case Token::Type::Rbracket:
                stream << "Rbracket";
                break;
            case Token::Type::String:
                stream << "String(" << token.value << ")";
                break;
            case Token::Type::Assign:
                stream << "Assign";
                break;
            case Token::Type::Unknown:
                stream << "Unknown(" << token.value << ")";
                break;
            case Token::Type::Eof:
                stream << "Eof";
                break;
        }
        return stream;
    }
}

std::ostream &operator<<(std::ostream &stream, IniParser::State state) {
    switch (state) {
        case IniParser::State::Expect_section_begin_or_key:
            stream << "Expect_section_begin_or_key";
            break;
        case IniParser::State::Expect_value:
            stream << "Expect_value";
            break;
        case IniParser::State::Expect_assign:
            stream << "Expect_assign";
            break;
        case IniParser::State::Expect_newline_or_eof:
            stream << "Expect_newline_or_eof";
            break;
        case IniParser::State::Expect_section_end:
            stream << "Expect_section_end";
            break;
        case IniParser::State::Finish:
            stream << "Finish";
            break;
        case IniParser::State::Expect_section_name:
            stream << "Expect_section_name";
            break;
    }
    return stream;
}

void IniParser::parse(std::istream &stream, Handler *handler) {
    Lexer lexer{stream};
    state_ = State::Expect_section_begin_or_key;
    while (state_ != State::Finish) {
        Token token = lexer.nextToken();
        LOG_DEBUG(logger, "State: " << state_ << ", token: " << token);
        switch (token.type) {
            case Token::Type::Lbracket:
                switch (state_) {
                    case State::Expect_section_begin_or_key:
                        state_ = State::Expect_section_name;
                        break;
                    default:
                        throw SyntaxError{lexer.error_msg("unexpected '[' symbol")};
                }
                break;
            case Token::Type::Rbracket:
                switch (state_) {
                    case State::Expect_section_end:
                        state_ = State::Expect_newline_or_eof;
                        break;
                    default:
                        throw SyntaxError{lexer.error_msg("unexpected ']' symbol")};
                }
                break;
            case Token::Type::String:
                switch (state_) {
                    case State::Expect_section_name:
                        if (handler) {
                            handler->onSection(token.value);
                        }
                        state_ = State::Expect_section_end;
                        break;
                    case State::Expect_section_begin_or_key:
                        if (handler) {
                            handler->onKey(token.value);
                        }
                        state_ = State::Expect_assign;
                        break;
                    case State::Expect_value:
                        if (handler) {
                            handler->onValue(token.value);
                        }
                        state_ = State::Expect_newline_or_eof;
                        break;
                    default:
                        throw SyntaxError{lexer.error_msg("unexpected string value '" + token.value + "'")};
                }
                break;
            case Token::Type::Newline:
                switch (state_) {
                    case State::Expect_newline_or_eof:
                        state_ = State::Expect_section_begin_or_key;
                        break;
                    case State::Expect_section_begin_or_key:  // skip empty lines
                        break;
                    case State::Expect_value:
                        if (handler) {
                            handler->onValue("");
                        }
                        state_ = State::Expect_section_begin_or_key;
                        break;
                    default:
                        throw SyntaxError{lexer.error_msg("Unexpected new line")};
                }
                break;
            case Token::Type::Assign:
                switch (state_) {
                    case State::Expect_assign:
                        state_ = State::Expect_value;
                        break;
                    default:
                        throw SyntaxError{lexer.error_msg("Unexpected '=' symbol")};
                }
                break;
            case Token::Type::Unknown:
                throw SyntaxError{lexer.error_msg("Unexpected symbol '" + token.value + "'")};
            case Token::Type::Eof:
                state_ = State::Finish;
                break;
        }
    }
};