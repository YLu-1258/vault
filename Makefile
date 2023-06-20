project_dir := /home/eris29/vscode/vault
source_dir := $(addsuffix /src,$(project_dir))
main_source := $(addsuffix /main.cpp,$(source_dir))
source := $(wildcard $(source_dir)/*.cpp)
include_dir := $(addsuffix /include,$(source_dir))
main_compiled := $(addsuffix /main,$(project_dir))
object_files := $(patsubst $(source_dir)/%.cpp,$(project_dir)/%.o,$(wildcard $(source_dir)/*.cpp))

clean:
	rm -rf $(main_compiled) $(object_files)

clear:
	clear

compile: 
	g++ -o $(main_compiled) $(source) -I$(include_dir) -lsqlite3 -lcrypto

recompile: | clean clear compile

test:
	echo $(header_files)
