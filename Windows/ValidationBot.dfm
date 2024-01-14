object ValidationBotDialog: TValidationBotDialog
  Left = 0
  Top = 0
  ActiveControl = ButtonBotRun
  BorderStyle = bsToolWindow
  Caption = 'Auto Validation Bot'
  ClientHeight = 163
  ClientWidth = 365
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  Position = poMainFormCenter
  OnKeyUp = FormKeyUp
  OnShow = FormShow
  TextHeight = 13
  object Label1: TLabel
    Left = 11
    Top = 11
    Width = 68
    Height = 13
    Caption = 'Path to CPU-Z'
  end
  object Label3: TLabel
    Left = 11
    Top = 37
    Width = 26
    Height = 13
    Caption = 'Sleep'
  end
  object Label5: TLabel
    Left = 141
    Top = 37
    Width = 5
    Height = 13
    Caption = 's'
  end
  object Label6: TLabel
    Left = 264
    Top = 39
    Width = 18
    Height = 13
    Alignment = taRightJustify
    Caption = 'FSB'
  end
  object Label7: TLabel
    Left = 262
    Top = 65
    Width = 20
    Height = 13
    Alignment = taRightJustify
    Caption = 'CPU'
  end
  object Label8: TLabel
    Left = 11
    Top = 63
    Width = 22
    Height = 13
    Caption = 'Step'
  end
  object Label9: TLabel
    Left = 141
    Top = 64
    Width = 79
    Height = 13
    Caption = 'MHz (0 for auto)'
  end
  object StatusBarBot: TStatusBar
    Left = 0
    Top = 144
    Width = 365
    Height = 19
    Panels = <>
    SimplePanel = True
    ExplicitTop = 115
  end
  object ButtonBotRun: TButton
    Left = 288
    Top = 121
    Width = 75
    Height = 25
    Caption = 'Run'
    TabOrder = 0
    OnClick = ButtonBotRunClick
  end
  object ButtonBrowseCpuz: TButton
    Left = 288
    Top = 6
    Width = 75
    Height = 25
    Caption = 'Browse...'
    TabOrder = 2
    OnClick = ButtonBrowseCpuzClick
  end
  object EditBotSleep: TEdit
    Left = 104
    Top = 34
    Width = 33
    Height = 21
    NumbersOnly = True
    TabOrder = 3
    Text = '6'
    OnChange = BotControlChange
  end
  object EditCpuzPath: TEdit
    Left = 104
    Top = 8
    Width = 178
    Height = 21
    TabOrder = 4
    OnChange = BotControlChange
  end
  object PanelCurrentFsb: TPanel
    Left = 289
    Top = 37
    Width = 74
    Height = 18
    BevelOuter = bvLowered
    Ctl3D = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentColor = True
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 5
  end
  object EditCoreFrequency: TPanel
    Left = 289
    Top = 63
    Width = 74
    Height = 18
    BevelOuter = bvLowered
    Ctl3D = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentColor = True
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 6
  end
  object CheckBoxUltra: TCheckBox
    Left = 11
    Top = 125
    Width = 110
    Height = 17
    Caption = 'Ultra (no update)'
    TabOrder = 7
    OnClick = BotControlChange
  end
  object EditFsbStep: TEdit
    Left = 104
    Top = 60
    Width = 33
    Height = 21
    NumbersOnly = True
    TabOrder = 8
    Text = '0'
    OnChange = BotControlChange
  end
  object ButtonSaveBotSettings: TButton
    Left = 207
    Top = 121
    Width = 75
    Height = 25
    Caption = 'Save'
    Enabled = False
    TabOrder = 9
    OnClick = ButtonSaveBotSettingsClick
  end
  object CheckBoxReverse: TCheckBox
    Left = 11
    Top = 99
    Width = 110
    Height = 17
    Caption = 'Reverse direction'
    TabOrder = 10
    OnClick = BotControlChange
  end
  object TimerBot: TTimer
    Enabled = False
    Interval = 6000
    OnTimer = TimerBotTimer
    Left = 136
    Top = 148
  end
  object OpenDialogBot: TOpenDialog
    DefaultExt = 'exe'
    Left = 168
    Top = 148
  end
end
