object ProfilePreloadForm: TProfilePreloadForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Load Profile'
  ClientHeight = 235
  ClientWidth = 310
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 11
    Width = 33
    Height = 13
    Caption = 'Author'
  end
  object Label2: TLabel
    Left = 8
    Top = 35
    Width = 45
    Height = 13
    Caption = 'Comment'
  end
  object Label3: TLabel
    Left = 8
    Top = 105
    Width = 40
    Height = 13
    Caption = 'Sections'
  end
  object CheckBoxTimings: TCheckBox
    Left = 72
    Top = 104
    Width = 97
    Height = 17
    Caption = 'Main Timings'
    Enabled = False
    TabOrder = 0
  end
  object CheckBoxDSSR: TCheckBox
    Left = 72
    Top = 127
    Width = 177
    Height = 17
    Caption = 'Drive Strength and Slew Rate'
    Enabled = False
    TabOrder = 1
  end
  object CheckBoxAdvanced: TCheckBox
    Left = 72
    Top = 150
    Width = 97
    Height = 17
    Caption = 'Advanced'
    Enabled = False
    TabOrder = 2
  end
  object CheckBoxRomsip: TCheckBox
    Left = 72
    Top = 173
    Width = 97
    Height = 17
    Caption = 'ROMSIP'
    Enabled = False
    TabOrder = 3
  end
  object ButtonLoadProfile: TButton
    Left = 228
    Top = 206
    Width = 75
    Height = 25
    Caption = 'Load'
    Default = True
    TabOrder = 4
    OnClick = ButtonLoadProfileClick
  end
  object ButtonCancel: TButton
    Left = 147
    Top = 206
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 5
  end
  object PanelComment: TMemo
    Left = 72
    Top = 32
    Width = 230
    Height = 66
    TabStop = False
    BevelInner = bvNone
    BevelKind = bkTile
    BorderStyle = bsNone
    Color = clBtnFace
    ReadOnly = True
    TabOrder = 6
    WantReturns = False
  end
  object PanelAuthor: TMemo
    Left = 72
    Top = 8
    Width = 230
    Height = 19
    TabStop = False
    BevelInner = bvNone
    BevelKind = bkTile
    BorderStyle = bsNone
    Color = clBtnFace
    ReadOnly = True
    TabOrder = 7
    WantReturns = False
    WordWrap = False
  end
end
