//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
#include "sqlite3.h"
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>

TSQLite *SQLite;
//---------------------------------------------------------------------------
__fastcall TSQLite::TSQLite(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSQLite::TableGetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)

{
  if(!Node) return;
  tableLoad *nodeData = (tableLoad *)Sender->GetNodeData(Node);
  switch(Column)
{
	case 0: CellText = nodeData->id;
	break;
	case 1: CellText = (UnicodeString)nodeData->url.c_str();
	break;
	case 2: CellText = nodeData->visit_count;
	break;
}

}
//---------------------------------------------------------------------------
void __fastcall TSQLite::DownloadClick(TObject *Sender)
{
int count;
const char * DBPath = "C:\\Users\\mikes\\Desktop\\SQLite\\Win32\\Debug\\History";
sqlite3* DB;
int rc = sqlite3_open(DBPath, &DB);
const char * TableSh = "Select * from urls;";
sqlite3_stmt * pStatement;
sqlite3_stmt * pStatementCount;
int queryResult = sqlite3_prepare_v2(DB, TableSh, -1, &pStatement, NULL);
if (queryResult != SQLITE_OK)
{
	std::cout << "SQL query error!!!" << std::endl;
	sqlite3_close(DB);
	sqlite3_finalize(pStatement);
}
const char * rowCount = "Select count(*) from urls;";
int queryCount = sqlite3_prepare_v2(DB, rowCount, -1, &pStatementCount, NULL);
PVirtualNode selectedNode = Table->AddChild(Table->RootNode);
tableLoad *nodeData = (tableLoad*) Table->GetNodeData(selectedNode);
int result1 = sqlite3_step(pStatementCount);
if (result1 == SQLITE_ROW)
{
count = sqlite3_column_int(pStatementCount, 0);
}
else return;
sqlite3_finalize(pStatementCount);
Table->Clear();
Table->NodeDataSize = sizeof(tableLoad);
Table->BeginUpdate();
for (int i = 0; i < count; i++) {
	PVirtualNode entryNode = Table->AddChild(Table->RootNode);
	tableLoad *nodeData = (tableLoad*) Table->GetNodeData(entryNode);
	int queryResult = sqlite3_step(pStatement);
	if (queryResult == SQLITE_ROW)
	{
		nodeData->id = sqlite3_column_int(pStatement, 0);
		nodeData->url = (UnicodeString)(char*)sqlite3_column_text(pStatement, 1);
		nodeData->visit_count = sqlite3_column_int(pStatement, 3);
	}
}
Table->EndUpdate();
sqlite3_close(DB);
sqlite3_finalize(pStatement);
}
//---------------------------------------------------------------------------
void __fastcall TSQLite::DeleteClick(TObject *Sender)
{
if (!Table->SelectedCount) {
	return;
}
const char * DBPath = "C:\\Users\\mikes\\Desktop\\SQLite\\Win32\\Debug\\History";
sqlite3* DB;
int rc = sqlite3_open(DBPath, &DB);
std::string insertQuery = "insert into temp (id) values ();";
std::size_t shift = insertQuery.find(");");
std::string clearQuery = "delete from temp;";
std::vector<int> indexVector;
PVirtualNode selectedNode = Table->GetFirstSelected();
tableLoad *nodeData = (tableLoad *)Table->GetNodeData(selectedNode);
indexVector.push_back(nodeData->id);
for (int i = 0; i < Table->SelectedCount - 1; i++) {
	selectedNode = Table->GetNextSelected(selectedNode);
	tableLoad *nodeData = (tableLoad *)Table->GetNodeData(selectedNode);
	indexVector.push_back(nodeData->id);
}
char *Err = 0;
int rc2 = sqlite3_exec(DB, clearQuery.c_str(), NULL, NULL, &Err);
Table->DeleteSelectedNodes();
for (std::vector<int>::iterator it = indexVector.begin();
	it != indexVector.end(); ++it){
	std::ostringstream vts;
	vts << *it;
	std::string subString = vts.str();
	std::string tempQuery = insertQuery;
	tempQuery.insert(shift, subString);
	int rc3 = sqlite3_exec(DB, tempQuery.c_str(), NULL, NULL, &Err);
	if( rc3 != SQLITE_OK ) {
		return;
	}
}
std::string deleteQuery = "delete from urls \
where id in (select id from temp);";
int rc4 = sqlite3_exec(DB, deleteQuery.c_str(), NULL, NULL, &Err);
if( rc4 != SQLITE_OK ) {
	return;
}
sqlite3_close(DB);
}
//---------------------------------------------------------------------------
void __fastcall TSQLite::DeleteAllClick(TObject *Sender)
{
int count;
const char * DBPath = "C:\\Users\\mikes\\Desktop\\SQLite\\Win32\\Debug\\History";
sqlite3* DB;
int rc = sqlite3_open(DBPath, &DB);
char *Err = 0;
std::string Delete = "delete from urls;";
int deleteTable = sqlite3_exec(DB, Delete.c_str(), NULL, NULL, &Err);
if (Err != 0)
{
	std::cout << "SQL table delete error!!!" << std::endl;
	sqlite3_close(DB);
}
const char * TableSh = "Select * from urls;";
sqlite3_stmt * pStatement;
sqlite3_stmt * pStatementCount;
int queryResult = sqlite3_prepare_v2(DB, TableSh, -1, &pStatement, NULL);
if (queryResult != SQLITE_OK)
{
	std::cout << "SQL query error!!!" << std::endl;
	sqlite3_close(DB);
	sqlite3_finalize(pStatement);
}
const char * rowCount = "Select count(*) from urls;";
int queryCount = sqlite3_prepare_v2(DB, rowCount, -1, &pStatementCount, NULL);
PVirtualNode selectedNode = Table->AddChild(Table->RootNode);
tableLoad *nodeData = (tableLoad*) Table->GetNodeData(selectedNode);
int result1 = sqlite3_step(pStatementCount);
if (result1 == SQLITE_ROW)
{
count = sqlite3_column_int(pStatementCount, 0);
}
else return;
sqlite3_finalize(pStatementCount);
Table->Clear();
Table->NodeDataSize = sizeof(tableLoad);
Table->BeginUpdate();
for (int i = 0; i < count; i++) {
	PVirtualNode entryNode = Table->AddChild(Table->RootNode);
	tableLoad *nodeData = (tableLoad*) Table->GetNodeData(entryNode);
	int queryResult = sqlite3_step(pStatement);
	if (queryResult == SQLITE_ROW)
	{
		nodeData->id = sqlite3_column_int(pStatement, 0);
		nodeData->url = (UnicodeString)(char*)sqlite3_column_text(pStatement, 1);
		nodeData->visit_count = sqlite3_column_int(pStatement, 3);
	}
}
Table->EndUpdate();
sqlite3_close(DB);
sqlite3_finalize(pStatement);
}
//---------------------------------------------------------------------------
