// parser.cpp

#include "uci_parser.hpp"


BBMove UCIParser::uci_to_bb(UCIMove uci_move) {
    int from_i, to_i;

    std::string from_str = uci_move.move.substr(0, 2);
    std::string to_str = uci_move.move.substr(2, 2);

    // Creates the corresponding move
    // TODO: Create an alternative structure without take and type
    from_i = Parser::pos_to_int(from_str);
    to_i = Parser::pos_to_int(to_str);
    return {from_i, to_i};
}

UCIMove UCIParser::bb_to_uci(BBMove bb_move) {
    std::string uci_str;
    uci_str += Parser::int_to_pos(bb_move.from);
    uci_str += Parser::int_to_pos(bb_move.to);
    return {uci_str};
}