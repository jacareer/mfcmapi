#pragma once
#include <UI/ViewPane/DropDownPane.h>
#include <UI/ViewPane/SplitterPane.h>
#include <UI/ViewPane/TreePane.h>
#include <core/smartview/SmartViewParser.h>

enum __ParsingTypeEnum;

namespace viewpane
{
	class SmartViewPane : public DropDownPane
	{
	public:
		static SmartViewPane* Create(int paneID, UINT uidLabel);

		void SetParser(__ParsingTypeEnum iParser);
		void Parse(const std::vector<BYTE>& myBin) { Parse(std::vector<std::vector<BYTE>>{myBin}); }
		void Parse(const std::vector<std::vector<BYTE>>& myBins);
		std::function<void(smartview::block*)> OnItemSelected = nullptr;

	private:
		void Initialize(_In_ CWnd* pParent, _In_ HDC hdc) override;
		void DeferWindowPos(_In_ HDWP hWinPosInfo, _In_ int x, _In_ int y, _In_ int width, _In_ int height) override;
		int GetFixedHeight() override;
		int GetLines() override;
		void RefreshTree();
		void AddChildren(HTREEITEM parent, const smartview::block& data);
		void ItemSelected(HTREEITEM hItem);
		void OnCustomDraw(_In_ NMHDR* pNMHDR, _In_ LRESULT* /*pResult*/, _In_ HTREEITEM hItemCurHover) const;
		void SetStringW(const std::wstring& szMsg);

		void SetMargins(
			int iMargin,
			int iSideMargin,
			int iLabelHeight, // Height of the label
			int iSmallHeightMargin,
			int iLargeHeightMargin,
			int iButtonHeight, // Height of buttons below the control
			int iEditHeight) override; // height of an edit control

		std::vector<std::vector<BYTE>> m_bins;
		smartview::block treeData;
		SplitterPane m_Splitter;
		TreePane* m_TreePane{nullptr};
		bool m_bHasData{false};
		bool m_bDoDropDown{true};
	};
} // namespace viewpane