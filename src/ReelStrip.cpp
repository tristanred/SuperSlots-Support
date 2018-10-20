#include "ReelStrip.h"

#include <stdlib.h>
#include <time.h>

#include <libtech/stringtools.h>

#include "SymbolSet.h"

#define PUGIXML_HEADER_ONLY
#include "pugixml.hpp"

ReelStrip::ReelStrip()
{
    this->Length = 0;
    this->Symbols = NULL;
}

ReelStrip::ReelStrip(Symbol** symbols, int length)
{
    this->Symbols = symbols;
    this->Length = length;
}

ReelStrip::~ReelStrip()
{
    delete[] this->Symbols;
}

ReelStrip** ReelStrip::GenerateReelstripSetFromConfig(const char* configPath, SymbolSet* symbols, int amount)
{
    if (amount == 0)
    {
        return NULL;
    }

    ReelStrip** rs_set = new ReelStrip*[amount];
    for (int i = 0; i < amount; i++)
    {
        rs_set[i] = NULL;
    }

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(configPath);
    if(!result)
    {
        // File not found
        return NULL;
    }

    // For now, read the reelstrip with id 0
    pugi::xpath_node_set reelStripNodes = doc.select_nodes("/reelsetConfig/reelset[@id = '0']/reelstrip");

    int rs_index = 0;
    for(pugi::xpath_node node: reelStripNodes)
    {
        pugi::xml_node reelStrip = node.node();

        const char* txt = reelStrip.text().as_string();

        long int amount = 0;
        int* numbers = convert_string_to_int_list(txt, &amount);

        rs_set[rs_index] = new ReelStrip();
        rs_set[rs_index]->Length = amount;
        rs_set[rs_index]->Symbols = new Symbol*[amount];
        
        for (int i = 0; i < amount; i++)
        {
            int num = numbers[i];
            rs_set[rs_index]->Symbols[i] = symbols->SymbolList[num];
        }
    }

    return rs_set;
}

ReelStrip* ReelStrip::GenerateRandomReelstrip(int length, SymbolSet* symbols)
{
    ReelStrip* rs = new ReelStrip();

    rs->Length = length;
    rs->Symbols = new Symbol*[length];

    for (int i = 0; i < length; i++)
    {
        rs->Symbols[i] = symbols->SymbolList[rand() % symbols->SymbolCount];
    }

    return rs;
}
