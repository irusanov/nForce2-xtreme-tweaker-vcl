object ProfileSaveForm: TProfileSaveForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Save Profile'
  ClientHeight = 260
  ClientWidth = 310
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 35
    Width = 33
    Height = 13
    Caption = 'Author'
  end
  object Label2: TLabel
    Left = 8
    Top = 59
    Width = 45
    Height = 13
    Caption = 'Comment'
  end
  object Label3: TLabel
    Left = 8
    Top = 129
    Width = 40
    Height = 13
    Caption = 'Sections'
  end
  object LabelProfileName: TLabel
    Left = 8
    Top = 11
    Width = 27
    Height = 13
    Caption = 'Name'
  end
  object CheckBoxTimings: TCheckBox
    Left = 72
    Top = 128
    Width = 97
    Height = 17
    Caption = 'Main Timings'
    Checked = True
    State = cbChecked
    TabOrder = 0
    OnClick = SectionCheckBoxClick
  end
  object CheckBoxDSSR: TCheckBox
    Left = 72
    Top = 151
    Width = 177
    Height = 17
    Caption = 'Drive Strength and Slew Rate'
    TabOrder = 1
    OnClick = SectionCheckBoxClick
  end
  object CheckBoxAdvanced: TCheckBox
    Left = 72
    Top = 174
    Width = 97
    Height = 17
    Caption = 'Advanced'
    TabOrder = 2
    OnClick = SectionCheckBoxClick
  end
  object CheckBoxRomsip: TCheckBox
    Left = 72
    Top = 197
    Width = 97
    Height = 17
    Caption = 'ROMSIP'
    TabOrder = 3
    OnClick = SectionCheckBoxClick
  end
  object ButtonSaveProfile: TButton
    Left = 228
    Top = 230
    Width = 75
    Height = 25
    Caption = 'Save...'
    Default = True
    TabOrder = 4
    OnClick = ButtonSaveProfileClick
  end
  object ButtonCancel: TButton
    Left = 147
    Top = 230
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 5
  end
  object PanelAuthor: TMemo
    Left = 72
    Top = 32
    Width = 230
    Height = 19
    BevelInner = bvLowered
    BevelOuter = bvNone
    MaxLength = 36
    TabOrder = 6
    WantReturns = False
    WordWrap = False
  end
  object PanelComment: TMemo
    Left = 72
    Top = 56
    Width = 230
    Height = 66
    BevelInner = bvLowered
    BevelOuter = bvNone
    MaxLength = 144
    TabOrder = 7
    WantReturns = False
  end
  object PanelName: TMemo
    Left = 72
    Top = 8
    Width = 230
    Height = 19
    BevelInner = bvLowered
    BevelOuter = bvNone
    MaxLength = 36
    TabOrder = 8
    WantReturns = False
    WordWrap = False
  end
  object SaveTextFileDialog1: TSaveTextFileDialog
    DefaultExt = 'profile'
    Filter = 'profile files (*.profile)|*.profile'
    Left = 8
    Top = 146
  end
end
