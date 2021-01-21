//
// Created by qianweicheng on 2020/5/15.
//

#ifndef A8_HTML_PARSER_HPP
#define A8_HTML_PARSER_HPP

#include <string>
#include <vector>
#include "rapidxml/rapidxml.hpp"

using namespace rapidxml_a8;

namespace a8 {
    typedef struct {
        std::string name;
        std::string attribute;
        std::string attributeValue;
        int type = 0;// 0: xpath="/", 1:from any child, xpath="*/"
    } XPathFilter;

    class HTMLParser {
    public:
        HTMLParser();

        bool Parse(const std::string &html);

        const xml_node<> *FindNode(const xml_node<> *parent, const std::vector<XPathFilter> &xpath);

        const std::vector<const xml_node<> *>
        FindNodes(const xml_node<> *parent, const std::vector<XPathFilter> &xpath);

        void PrintNode(const xml_node<> *root);

    private:

        bool MatchFilter(const xml_node<> *node, XPathFilter &filter);

        const xml_node<> *
        FindNodeInternal(const xml_node<> *parent, const std::vector<XPathFilter> &xpath, const int currentIndex);

        void FindNodesInternal(std::vector<const xml_node<> *> &results, const xml_node<> *parent,
                               const std::vector<XPathFilter> &xpath, const int currentIndex);

        void PrintInternal(const xml_node<> *root, const int level);

    private:
        std::unique_ptr<xml_document<>> doc = std::make_unique<xml_document<>>();
    };

}


#endif //A8_HTML_PARSER_HPP
