#pragma once

class SymbolSet;
class Symbol;

class ReelStrip
{
public:
    ReelStrip();
    ReelStrip(Symbol** symbols, int length);
    ~ReelStrip();

    int Length;
    Symbol** Symbols; // Borrowed list

    static ReelStrip* GenerateReelstripFromConfig(const char* configPath, SymbolSet* symbols);
    static ReelStrip* GenerateRandomReelstrip(int length, SymbolSet* symbols);

};

/**
 * Reelstrip file format
 *
 * reelstrip.conf
 * <reelsetConfig>                  # Root node
 *   <reelset id="0">               # Node for 1 set of reels
 *      <reelstrip reel="0">
 *          1, 2, 3, 4, 5, 6, 7, 8, 9, 0
 *      </reelstrip>
 *      <reelstrip reel="1">
 *          1, 2, 3, 4, 5, 6, 7, 8, 9, 0
 *      </reelstrip>
 *      <reelstrip reel="2">
 *          1, 2, 3, 4, 5, 6, 7, 8, 9, 0
 *      </reelstrip>
 *      <reelstrip reel="3">
 *          1, 2, 3, 4, 5, 6, 7, 8, 9, 0
 *      </reelstrip>
 *      <reelstrip reel="4">
 *          1, 2, 3, 4, 5, 6, 7, 8, 9, 0
 *      </reelstrip>
 *   </reelset>
 *   <reelset id="1">
 *      <reelstrip reel="0">
 *          1, 2, 3, 4, 5, 6, 7, 8, 9, 0
 *      </reelstrip>
 *      <reelstrip reel="1">
 *          1, 2, 3, 4, 5, 6, 7, 8, 9, 0
 *      </reelstrip>
 *      <reelstrip reel="2">
 *          1, 2, 3, 4, 5, 6, 7, 8, 9, 0
 *      </reelstrip>
 *      <reelstrip reel="3">
 *          1, 2, 3, 4, 5, 6, 7, 8, 9, 0
 *      </reelstrip>
 *      <reelstrip reel="4">
 *          1, 2, 3, 4, 5, 6, 7, 8, 9, 0
 *      </reelstrip>
 *   </reelset>
 * </reelsetConfig>
 */