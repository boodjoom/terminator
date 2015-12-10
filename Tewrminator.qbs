import qbs

CppApplication {
    type: "application" // To suppress bundle generation on Mac
    consoleApplication: true
    cpp.includePaths: ["stdperiph/inc/", "inc/", "./"]
    files: ["stdperiph/inc/*.h",
	"stdperiph/src/*.c",
	"inc/*.h",
	"src/*.c",
	"*.h",
	"main.c"]
    cpp.defines: ["STM8S003"]
    Group {     // Properties for the produced executable
        fileTagsFilter: product.type
        qbs.install: true
    }
}

