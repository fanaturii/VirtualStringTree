object SQLite: TSQLite
  Left = 0
  Top = 0
  Caption = 'SQLite'
  ClientHeight = 800
  ClientWidth = 1122
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Table: TVirtualStringTree
    Left = 24
    Top = 32
    Width = 849
    Height = 753
    Header.AutoSizeIndex = 0
    Header.Options = [hoAutoResize, hoColumnResize, hoDrag, hoHotTrack, hoShowSortGlyphs, hoVisible]
    TabOrder = 0
    TreeOptions.PaintOptions = [toShowButtons, toShowDropmark, toShowHorzGridLines, toShowRoot, toThemeAware, toUseBlendedImages, toFullVertGridLines, toShowFilteredNodes]
    OnGetText = TableGetText
    Columns = <
      item
        Position = 0
        Text = 'ID'
        Width = 84
      end
      item
        Position = 1
        Text = 'URL'
        Width = 689
      end
      item
        Position = 2
        Text = 'Visit Count'
        Width = 72
      end>
  end
  object Download: TButton
    Left = 888
    Top = 32
    Width = 217
    Height = 49
    Caption = 'Download'
    TabOrder = 1
    OnClick = DownloadClick
  end
  object Delete: TButton
    Left = 888
    Top = 104
    Width = 217
    Height = 49
    Caption = 'Delete'
    TabOrder = 2
    OnClick = DeleteClick
  end
  object DeleteAll: TButton
    Left = 888
    Top = 176
    Width = 217
    Height = 49
    Caption = 'DeleteAll'
    TabOrder = 3
    OnClick = DeleteAllClick
  end
end
