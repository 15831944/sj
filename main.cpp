#include "node/Node.h"
#ifdef __GNUC__
#include <unistd.h>
#include <dirent.h>
#define PATH_SEPERATOR "/"
#endif
#ifdef _MSC_VER 
#include <direct.h>
#define getcwd _getcwd
#include "windows/dirent.h"
#define PATH_SEPERATOR "\\"
#endif
#include <string.h>
#include <fstream>

void testWhile() {
    shared_ptr<CResult> result;
    Compiler compiler;
    
    result = compiler.run("while false {}");
    assert(result->type == RESULT_VOID);
    
    result = compiler.run("while 1.0 {}");
    assert(result->type == RESULT_ERROR && result->errors[0].code == CErrorCode::TypeMismatch);
    
    result = compiler.run("x = 10; while x > 0 { x = x - 1 }; x");
    assert(result->type == RESULT_INT && result->iResult == 0);
}

void testFunction() {
    shared_ptr<CResult> result;
    Compiler compiler;
    
    result = compiler.run("func() { 1 }");
    assert(result->type == RESULT_VOID);

    result = compiler.run("func() { 1 }; func()");
    assert(result->type == RESULT_INT && result->iResult == 1);

    result = compiler.run("func() { func() }; func()");
    assert(result->type == RESULT_ERROR && result->errors[0].code == CErrorCode::TypeLoop);

    result = compiler.run("func() { -3.0 }; func() < 4.0");
    assert(result->type == RESULT_BOOL && result->bResult == true);

    result = compiler.run("func(x: 1) { x }; func()");
    assert(result->type == RESULT_INT && result->iResult == 1);

    result = compiler.run("func(x: 1) { x }; func(2)");
    assert(result->type == RESULT_INT && result->iResult == 2);

    result = compiler.run("func(x: 1) { x }; func(x: 3)");
    assert(result->type == RESULT_INT && result->iResult == 3);

    result = compiler.run("func(x: 1, y: 2) { x + y }; func(y: 1)");
    assert(result->type == RESULT_INT && result->iResult == 2);

    result = compiler.run("func(x: 1, y: 2) { x + y }; func(2, y: 1)");
    assert(result->type == RESULT_INT && result->iResult == 3);

    result = compiler.run("func(x: 1, y: 2) { x + y }; func(y: 1, 1)");
    assert(result->type == RESULT_ERROR && result->errors[0].code == CErrorCode::ParameterByIndexAfterByName);

    result = compiler.run("func(x: 1, y: 2) { x + y }; func(y: 1, y: 1)");
    assert(result->type == RESULT_ERROR && result->errors[0].code == CErrorCode::ParameterRedefined);

    result = compiler.run("func(x: 1, y: 2) { x + y }; func(q: 1)");
    assert(result->type == RESULT_ERROR && result->errors[0].code == CErrorCode::ParameterDoesNotExist);

    result = compiler.run("func(x: 1, y: 2) { x + y }; func(1, 2, 3)");
    assert(result->type == RESULT_ERROR && result->errors[0].code == CErrorCode::TooManyParameters);

    result = compiler.run("func(x: 1, y: 2) { x + y }; func(1.0)");
    assert(result->type == RESULT_ERROR && result->errors[0].code == CErrorCode::TypeMismatch);

    result = compiler.run("func(x: 'int) { x }; func(1)");
    assert(result->type == RESULT_INT && result->iResult == 1);

    result = compiler.run("func(x: 'float) { x }; func(1.0)");
    assert(result->type == RESULT_FLOAT && result->fResult == 1.0);

    result = compiler.run("func(x: 'float) { x }; func(1)");
    assert(result->type == RESULT_ERROR && result->errors[0].code == CErrorCode::TypeMismatch);

    result = compiler.run("func(x: 'int) { x }; func()");
    assert(result->type == RESULT_ERROR && result->errors[0].code == CErrorCode::ParameterRequired);

    result = compiler.run(R"DELIM(
        func(x: 'int)'int {
            if x > 0 {
                func(x - 1)
            } else {
                0
            }
        }
        func(4)
    )DELIM");
    assert(result->type == RESULT_INT && result->iResult == 0);

    result = compiler.run(R"DELIM(
        bar() { 9 }
        func() {
            bar()
        }
        func()
    )DELIM");
    assert(result->type == RESULT_INT && result->iResult == 9);

    result = compiler.run(R"DELIM(
        func(
            bar() { 9 }
        ) {
            bar()
        }
        func()
    )DELIM");
    assert(result->type == RESULT_INT && result->iResult == 9);

    result = compiler.run(R"DELIM(
		foo() {
			void
		}
		foo()
    )DELIM");
    assert(result->type == RESULT_VOID);
}

void testClass() {
    shared_ptr<CResult> result;
    Compiler compiler;
    
    result = compiler.run("class(x: 0) { this }");
    assert(result->type == RESULT_VOID);
    
    result = compiler.run("class(b : 0) { this }; a : class(); a.b = 1");
    assert(result->type == RESULT_ERROR && result->errors[0].code == CErrorCode::ImmutableAssignment);

    result = compiler.run("class(a.b : 0) { this }");
    assert(result->type == RESULT_ERROR && result->errors[0].code == CErrorCode::InvalidDot);
    
    result = compiler.run("class(b = 0) { this }; a : class(); a.b = 1");
    assert(result->type == RESULT_INT && result->iResult == 1);

    result = compiler.run("class(x: 0) { this }\n"
                          "c: class()\n"
                          "c.x");
    assert(result->type == RESULT_INT && result->iResult == 0);
    
    result = compiler.run("class(x: 0) { this }\n"
                          "c: class(x: 1)\n"
                          "c.x");
    assert(result->type == RESULT_INT && result->iResult == 1);
    
    result = compiler.run("class(x: 0) { this }\n"
                          "c: class(1)\n"
                          "c.x");
    assert(result->type == RESULT_INT && result->iResult == 1);
    
    result = compiler.run("class(x: 0, y: 0) { this }\n"
                          "c: class(1, 2)\n"
                          "c.x + c.y");
    assert(result->type == RESULT_INT && result->iResult == 3);
    
    result = compiler.run("class(func() { 1 }) { this }\n"
                          "c: class()\n"
                          "c.func()");
    assert(result->type == RESULT_INT && result->iResult == 1);

    result = compiler.run("class(x:0, func() { x }) { this }\n"
                          "c: class(1)\n"
                          "c.func()");
    assert(result->type == RESULT_INT && result->iResult == 1);

    result = compiler.run(R"DELIM(
        class(x : 0) { this }
        func() { class(1) }
        func().x
    )DELIM");
    assert(result->type == RESULT_INT && result->iResult == 1);

    result = compiler.run(R"DELIM(
		class(
			foo(x: 'int) {
				if x > 0 {
					bar(x - 1)
				} else {
					0
				}
			}
			bar(x: 0) {
				foo(x)
			}
		) { this }
		c: class()
		c.foo(4)
    )DELIM");
    assert(result->type == RESULT_INT && result->iResult == 0);

    result = compiler.run(R"DELIM(
		math(
			sub(x: 'int, y: 'int) {
				x - y
			}
		) { this }
		class(
			m: math()
			foo(x: 0) {
				if x > 0 {
					bar(m.sub(x, 1))
				} else {
					0
				}
			}
			bar(x: 0) {
				foo(x)
			}
		) { this }
		c: class()
		c.foo(4)
    )DELIM");
    assert(result->type == RESULT_INT && result->iResult == 0);

    result = compiler.run(R"DELIM(
        class() {
			m: 1
			inner() {
				m
			}
			inner()
		}
        class()
    )DELIM");
    assert(result->type == RESULT_INT && result->iResult == 1);
    
    result = compiler.run(R"DELIM(
		math: ^(
                sub(x: 'int, y: 'int) {
				x - y
			}
		) { this }
		class(
			foo(x: 0) {
				if x > 0 {
					bar(math.sub(x, 1))
				} else {
					0
				}
			}
			bar(x: 0) {
				foo(x)
			}
		) { this }
		c: class()
		c.foo(4)
    )DELIM");
    assert(result->type == RESULT_INT && result->iResult == 0);

    result = compiler.run(R"DELIM(
        a(
            x: 1
            b: aa(
                c() { x }
            ) { this }
        ) { this }
        a: a()
        a.b.c()
        d: a.b
        d.c()
    )DELIM");
    assert(result->type == RESULT_INT && result->iResult == 1);
}

void testTemplate() {
    shared_ptr<CResult> result;
    Compiler compiler;
    
    result = compiler.run(R"DELIM(
        class!t() { 1 }
        a: class!int()
        b: class!float()
        c: class!bool()
    )DELIM");
    assert(result->type != RESULT_ERROR);

    result = compiler.run(R"DELIM(
        class!t(
            x:'t
        ) { this }
        c: class!int(1)
        c.x
    )DELIM");
    assert(result->type == RESULT_INT && result->iResult == 1);
    
    result = compiler.run(R"DELIM(
                          class![t1, t2]() { 1 }
                          a: class![int, bool]()
                          c: class![bool, float]()
                          )DELIM");
    assert(result->type != RESULT_ERROR);
    
    result = compiler.run(R"DELIM(
        class!t() { 1 }
        func() { }
        d: class!func()
    )DELIM");
    assert(result->type != RESULT_ERROR);
    
    result = compiler.run(R"DELIM(
                          class![t1, t2]() { 1 }
                          func() { }
                          b: class![float, func]()
                          d: class![func, int]()
                          )DELIM");
    assert(result->type != RESULT_ERROR);
    
    result = compiler.run(R"DELIM(
                          class!t() { 1 }
                          func!t() { 1 }
                          d: class![func!int]()
                          )DELIM");
    assert(result->type != RESULT_ERROR);
    
    result = compiler.run(R"DELIM(
                          class!t(
                                  func!t() { 1 }
                                  ) { this }
                          c: class!int()
                          1
                          )DELIM");
    assert(result->type != RESULT_ERROR);
}
                          
void testArray() {
    shared_ptr<CResult> result;
    Compiler compiler;
    
    result = compiler.run(R"DELIM(
        a : array!int(1)
        a.set(0, 1)
        c : a.get(0)
        a.delete(1)
        c
    )DELIM");
    assert(result->type == RESULT_INT && result->iResult == 1);

    result = compiler.run(R"DELIM(
        class(x: 0) { this }
        a : array!class(1)
        a.set(0, class(1))
        b : a.get(0)
        c : b.x
        a.delete(1)
        c
    )DELIM");
    assert(result->type == RESULT_INT && result->iResult == 1);
    
    result = compiler.run(R"DELIM(
        include "list.sj"
        
        a : [1, 2, 3]
        a[0] = 2		// find method 'set'
        a[0]			// find method 'get'
    )DELIM");
    assert(result->type == RESULT_INT && result->iResult == 2);
    
    result = compiler.run(R"DELIM(
        include "list.sj"
        
        class(x : 'int) { this }
        a : [class(1), class(2), class(3)]
        c : a[0]
        c.x
    )DELIM");
    assert(result->type == RESULT_INT && result->iResult == 1);

    result = compiler.run(R"DELIM(
        include "list.sj"
        
        class(x : 'int) { this }
        a: list!class()
        for x: 1 to 100000 {
            a.add(class(x))
        }
        c : a[0]
        c.x
        )DELIM");
    assert(result->type == RESULT_INT && result->iResult == 1);
}

void testInclude() {
    shared_ptr<CResult> result;
    Compiler compiler;

    result = compiler.run(R"DELIM(
                          include "list.sj"
                          
                          a : [1]
                          a[0] = 3
                          a[0]
                        )DELIM");
    assert(result->type == RESULT_INT && result->iResult == 3);


    result = compiler.run(R"DELIM(
                          class() {
                              include "list.sj"
                          }
                          )DELIM");
    assert(result->type == RESULT_ERROR && result->errors[0].code == CErrorCode::IncludeOnlyInGlobal);

    result = compiler.run(R"DELIM(
                          include "common.sj"

                          a : [1]
                          a[0] = 3
                          a[0]
                          )DELIM");
    assert(result->type == RESULT_INT && result->iResult == 3);
}

void testString() {
    shared_ptr<CResult> result;
    Compiler compiler;

    result = compiler.run(R"DELIM(
                        include "list.sj"
                          
                          a : "hello"
                          c : a[0]
                          c == 'h'
                        )DELIM");
    assert(result->type == RESULT_BOOL && result->bResult);

    result = compiler.run(R"DELIM(
                          include "list.sj"
                          "hello"
                          )DELIM");
    assert(result->type == RESULT_STR && result->strResult == "hello");

    result = compiler.run("'\n'");
    assert(result->type == RESULT_CHAR && result->cResult == '\n');

    result = compiler.run("'\''");
    assert(result->type == RESULT_CHAR && result->cResult == '\'');

    result = compiler.run(R"DELIM(
                          include "list.sj"
                          "he\nllo"
                          )DELIM");
    assert(result->type == RESULT_STR && result->strResult == "he\nllo");

    result = compiler.run(R"DELIM(
                          include "list.sj"
                          "he\"llo"
                          )DELIM");
    assert(result->type == RESULT_STR && result->strResult == "he\"llo");
}

void testHeap() {
    shared_ptr<CResult> result;
    Compiler compiler;

    result = compiler.run(R"DELIM(
                          bar(f = foo(1)) { this }
                          foo(x : 0) { this }
                          
                          func(b : 'bar) {
                              b.f = foo(2) // callvar("foo") is heap because it is store in a non-local var
                          }
                          
                          b : bar() // callvar("boo") is stack because it is stored in a local var
                          func(b).x
    )DELIM");
    assert(result->type == RESULT_INT && result->iResult == 2);
}

void testInterface() {
    shared_ptr<CResult> result;
    Compiler compiler;

    result = compiler.run(R"DELIM(
        #foo()
        
        class #foo () { this }

        a: class() as #foo

        void
    )DELIM");
    assert(result->type == RESULT_VOID);
    
    result = compiler.run(R"DELIM(
        #foo(
            test()'int
        )
        
        class #foo (
            test() {
                5
            }
        ) { this }

        a: class() as #foo
        a.test()
    )DELIM");
    assert(result->type == RESULT_INT && result->iResult == 5);

    result = compiler.run(R"DELIM(
        include "common.sj"
        
        #foo(
            test()'list!char
        )
        
        class #foo (
            test() {
                "5"
            }
        ) { this }

        a: class() as #foo
        a.test()
    )DELIM");
    assert(result->type != RESULT_ERROR);

    result = compiler.run(R"DELIM(
        #foo!item(
            test()'item
        )
        
        class #foo!int (
            test() {
                5
            }
        ) { this }

        a: class() as #foo!int
        a.test()
    )DELIM");
    assert(result->type != RESULT_ERROR);

    result = compiler.run(R"DELIM(
        #foo!item(
            test()'item
        )
        
        class!item #foo!item (
            test() {
                5
            }
        ) { this }

        a: class!int() as #foo!int
        a.test()
    )DELIM");
    assert(result->type != RESULT_ERROR);
    
    // TODO: test interface as heap var
    // TODO: test interface with heap var arg
    // TODO: test interface with heap var return
}

void runTest(std::string path, bool updateResult) {
	if (*(path.end() - 2) == 's' && *(path.end() - 1) == 'j') {
		printf("Running %s\n", path.c_str());

		auto codeFileName = path;
		codeFileName.replace(codeFileName.end() - 3, codeFileName.end(), ".c");
		auto errorFileName = path;
		errorFileName.replace(errorFileName.end() - 3, errorFileName.end(), ".errors");

		if (updateResult) {
			ofstream code;
			code.open(codeFileName);
			ofstream error;
			error.open(errorFileName);

			Compiler compiler;
			compiler.transpile(path, code, error);

			code.close();
			error.close();
		} else {
			stringstream codeA;
			stringstream errorA;

			Compiler compiler;
			compiler.transpile(path, codeA, errorA);

			codeA.seekg(0, codeA.beg);
			errorA.seekg(0, errorA.beg);

			// Compare file output
			int line = 0;
			string lineA;
			string lineB;
			ifstream codeB(codeFileName);
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
			ifstream errorB(errorFileName);
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

void runAllTests(std::string path, bool updateResult) {
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(path.c_str())) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) {
			if (ent->d_type == DT_DIR && strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..")) {
				string directoryPath = path;
				directoryPath.append(PATH_SEPERATOR).append(ent->d_name);
				runAllTests(directoryPath, updateResult);
			} else if (ent->d_type == DT_REG) {
				string filePath = path;
				filePath.append(PATH_SEPERATOR).append(ent->d_name);
				runTest(filePath, updateResult);
			}
		}
		closedir(dir);
	}
}
                          
int main(int argc, char **argv) {
    shared_ptr<CResult> result;
    Compiler compiler;
    
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    
    if (argc == 1) {
        printf("-test or [filename]\n");
        return 0;
    }
    
	if (strcmp(argv[1], "-test") == 0) {
		runAllTests(".", false);
	} else if (strcmp(argv[1], "-testUpdate") == 0) {
		runAllTests(".", true);
    } else {
        result = compiler.compile(argv[1]);
        for (auto error : result->errors) {
            printf("ERROR: %s %d:%d %d %s\n", error.fileName->c_str(), error.line, error.col, error.code, error.msg.c_str());
        }

        for (auto warning : result->warnings) {
            printf("WARNING: %s %d:%d %d %s\n", warning.fileName->c_str(), warning.line, warning.col, warning.code, warning.msg.c_str());
        }
        
        if (result->errors.size() == 0) {
            printf("SUCCESS\n");
            return 0;
        } else {
            return -1;
        }
    }

    return 0;
}
