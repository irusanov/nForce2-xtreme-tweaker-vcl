object SettingsForm: TSettingsForm
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = 'Options'
  ClientHeight = 96
  ClientWidth = 288
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
  object CheckBoxMinimizeToTray: TCheckBox
    Left = 8
    Top = 8
    Width = 97
    Height = 17
    Caption = 'Minimize to tray'
    TabOrder = 0
    OnClick = CheckBoxMinimizeToTrayClick
  end
  object CheckBoxSaveWindowPosition: TCheckBox
    Left = 8
    Top = 31
    Width = 169
    Height = 17
    Caption = 'Save window position on close'
    TabOrder = 1
    OnClick = CheckBoxSaveWindowPositionClick
  end
  object ButtonApplySettings: TButton
    Left = 208
    Top = 64
    Width = 75
    Height = 25
    Caption = 'Apply'
    Default = True
    Enabled = False
    TabOrder = 2
    OnClick = ButtonApplySettingsClick
  end
  object ButtonResetSettings: TButton
    Left = 8
    Top = 64
    Width = 75
    Height = 25
    Caption = 'Reset'
    TabOrder = 3
    OnClick = ButtonResetSettingsClick
  end
  object ButtonCancel: TButton
    Left = 127
    Top = 64
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Close'
    ModalResult = 2
    TabOrder = 4
  end
end
