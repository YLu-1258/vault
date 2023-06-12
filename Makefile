project_dir := /home/eris29/vscode/vault 
main_source := $(addsuffix /src/vault.cpp,$(project_dir))
main_compiled := $(addsuffix vault,$(project_dir))
include_dir := $(addsuffix /src/include,$(project_dir))
header_files := $(wildcard $(include_dir)/*.h)

clean:
	rm -rf vault_compiled

clear:
	clear

compile:
	g++ $(vault_source) -I $(include_dir) -l sqlite3 -o vault	

recompile: | clean clear compile

test:
	echo $(header_files)
