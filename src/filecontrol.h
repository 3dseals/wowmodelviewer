#ifndef FILECONTROL_H
#define FILECONTROL_H

#include "FileTreeItem.h"

class ModelViewer;

#include <wx/string.h>
#include <wx/treectrl.h> // wxTreeItemId

class FileControl: public wxWindow
{
	DECLARE_CLASS(FileControl)
	DECLARE_EVENT_TABLE()

	std::set<FileTreeItem> filelist;
public:
	// Constructor + Deconstructor
	FileControl(wxWindow* parent, wxWindowID id);
	~FileControl();

	void Init(ModelViewer* mv=NULL);
	void OnTreeSelect(wxTreeEvent &event);
	void OnTreeCollapsedOrExpanded(wxTreeEvent &event);
	void OnButton(wxCommandEvent &event);
	void OnChoice(wxCommandEvent &event);
	void OnTreeMenu(wxTreeEvent &event);
	void OnPopupClick(wxCommandEvent &evt);
	void Export(wxString val, int select);
	wxString ExportPNG(wxString val);
	void UpdateInterface();

	wxTreeCtrl *fileTree;
	wxButton *btnSearch;
	wxTextCtrl *txtContent;
	wxChoice *choFilter;
	int filterMode;
	wxTreeItemId CurrentItem;

	ModelViewer* modelviewer; // point to parent

private:
	void ClearCanvas();
};

class FileTreeData:public wxTreeItemData
{
public:
	wxString fn;
	FileTreeData(wxString fn):fn(fn) {}
};

#endif
