project_dir := /home/eris29/vscode/vault 
vault := $(addsuffix /src/vault.cpp,$(project_dir))
include := $(addsuffix /src/include,$(project_dir))
vault:
	g++ $(vault) -I $(include) -l sqlite3 -o vault	

test:
	echo $(vault)
