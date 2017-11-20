#pragma once

#include "TrBlock.h"

class TrOutput {
public:
	map<string, shared_ptr<TrBlock>> functions;
	map<string, vector<string>> structs;
    vector<string> structOrder;
    map<string, string> strings;
    map<string, bool> includes;
    vector<string> ccodeDefines;
    vector<string> ccodeFunctions;
	TrBlock mainFunction;

    TrOutput();
	void writeToStream(ostream& stream, bool hasMainLoop);
};
