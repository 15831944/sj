#include "node/Node.h"
#include <string.h>
#include <fstream>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

void runTest(fs::path path, bool updateResult) {    
	if (path.extension().string().compare(".sj") == 0) {
		printf("Running %s\n", path.string().c_str());
        TrBlock::resetVarNames();

        auto codeFileName = fs::change_extension(path, ".c");
        auto debugFileName = fs::change_extension(path, ".debug");
        auto errorFileName = fs::change_extension(path, ".errors");

		if (updateResult) {
			ofstream code;
			code.open(codeFileName.c_str());
			ofstream error;
			error.open(errorFileName.c_str());
            ofstream debug;
            debug.open(debugFileName.c_str());

			Compiler compiler;
			compiler.transpile(path.string(), code, error, &debug);

			code.close();
			error.close();
            debug.close();
		} else {
			stringstream codeA;
			stringstream errorA;

			Compiler compiler;
			compiler.transpile(path.string(), codeA, errorA, nullptr);

			codeA.seekg(0, codeA.beg);
			errorA.seekg(0, errorA.beg);

			// Compare file output
			int line = 0;
			string lineA;
			string lineB;
			ifstream codeB(codeFileName.c_str());
			if (codeB.is_open())
			{
				while (getline(codeB, lineB))
				{
					line++;
					getline(codeA, lineA);

					if (lineA.compare(lineB) != 0) {
						cout << "Line " << line << " does not match:\n" << lineA << "\n" << lineB << "\n";
					}
				}
				codeB.close();
			}

			// Compare error output
			line = 0;
			ifstream errorB(errorFileName.c_str());
			if (errorB.is_open())
			{
				while (getline(errorB, lineB))
				{
					line++;
					getline(errorA, lineA);

					if (lineA.compare(lineB) != 0) {
						cout << "Error " << line << " does not match:\n" << lineA << "\n" << lineB << "\n";
					}
				}
				errorB.close();
			}
		}
	}
}

void runAllTests(fs::path path, bool updateResult, const char* wildcard) {
    for (auto child : fs::directory_iterator(path)) {
        if (fs::is_regular_file(child.path()) && (wildcard == nullptr || child.path().generic_string().find(wildcard) != string::npos)) {
            runTest(child.path(), updateResult);
        }
    }
}
                          
int main(int argc, char **argv) {
    shared_ptr<CResult> result;
    Compiler compiler;
    
    if (argc == 1) {
        printf("-test or [filename]\n");
        return 0;
    }
    
	if (strcmp(argv[1], "-test") == 0) {
        runAllTests("app", false, argv[2]);
		runAllTests("basic", false, argv[2]);
	} else if (strcmp(argv[1], "-testUpdate") == 0) {
        runAllTests("app", true, argv[2]);
        runAllTests("basic", true, argv[2]);
    } else {
        auto path = fs::path(argv[1]);
        auto codeFileName = fs::change_extension(path, ".c");
        ofstream code;
        code.open(codeFileName.c_str());

        Compiler compiler;
        compiler.transpile(path.string(), code, cerr, nullptr);
    }

    return 0;
}
