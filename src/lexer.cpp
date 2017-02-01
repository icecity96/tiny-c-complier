//
// Created by ice_city on 1/25/17.
//
//TODO: test
#include "src/catch_main.hpp"
#include "lexer.hpp"

TEST_CASE("test lexer works ","[lexer]")
{
    std::ifstream file("../test_source");
    read_source(file);
    REQUIRE(get_next_token().id == get_cate_id("int"));
    REQUIRE(get_next_token().id == CATEGORY_MAP.at("ID"));
    REQUIRE(get_next_token().tag == "SEP");
    REQUIRE(get_next_token().tag == "if");
    REQUIRE(get_next_token().tag == "SEP");
    REQUIRE(get_next_token().id == CATEGORY_MAP.at("ID"));
    REQUIRE(get_next_token().id == CATEGORY_MAP.at("="));
    REQUIRE(get_next_token().id == CATEGORY_MAP.at("INT10"));
    REQUIRE(get_next_token().value == ")");
    REQUIRE(get_next_token().value == "{");
    REQUIRE(get_next_token().id == get_cate_id("while"));
    REQUIRE(get_next_token().id == get_cate_id("("));
    REQUIRE(get_next_token().id == get_cate_id("INT10"));
    REQUIRE(get_next_token().id == get_cate_id(")"));
    REQUIRE(get_next_token().value == ";");
    REQUIRE(get_next_token().value == "}");
}
