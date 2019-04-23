//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VirtualTrees.hpp"
#include <string>
//---------------------------------------------------------------------------
class TSQLite : public TForm
{
__published:	// IDE-managed Components
	TVirtualStringTree *Table;
	TButton *Download;
	TButton *Delete;
	TButton *DeleteAll;
	void __fastcall TableGetText(TBaseVirtualTree *Sender, PVirtualNode Node, TColumnIndex Column,
          TVSTTextType TextType, UnicodeString &CellText);
	void __fastcall DownloadClick(TObject *Sender);
	void __fastcall DeleteClick(TObject *Sender);
	void __fastcall DeleteAllClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    typedef struct {
	int id;
	UnicodeString url;
	int visit_count;
	} tableLoad;
	__fastcall TSQLite(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSQLite *SQLite;
//---------------------------------------------------------------------------
#endif
