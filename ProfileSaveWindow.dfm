object ProfileSaveForm: TProfileSaveForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Save Profile'
  ClientHeight = 102
  ClientWidth = 311
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
  object CheckBoxTimings: TCheckBox
    Left = 8
    Top = 8
    Width = 97
    Height = 17
    Caption = 'Main timings'
    Checked = True
    State = cbChecked
    TabOrder = 0
  end
  object CheckBoxDSSR: TCheckBox
    Left = 8
    Top = 31
    Width = 177
    Height = 17
    Caption = 'Drive Strength and Slew Rate'
    TabOrder = 1
  end
  object CheckBoxAdvanced: TCheckBox
    Left = 8
    Top = 54
    Width = 97
    Height = 17
    Caption = 'Advanced'
    TabOrder = 2
  end
  object CheckBoxRomsip: TCheckBox
    Left = 8
    Top = 77
    Width = 97
    Height = 17
    Caption = 'RIOMSIP'
    TabOrder = 3
  end
  object ButtonSaveProfile: TButton
    Left = 230
    Top = 73
    Width = 75
    Height = 25
    Caption = 'Save As...'
    TabOrder = 4
    OnClick = ButtonSaveProfileClick
  end
  object ButtonCancel: TButton
    Left = 230
    Top = 42
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 5
  end
  object SaveTextFileDialog1: TSaveTextFileDialog
    DefaultExt = 'profile'
    Filter = 'profile files (*.profile)|*.profile'
    Left = 240
    Top = 65528
  end
end
