object ValidationBotDialog: TValidationBotDialog
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsToolWindow
  Caption = 'Auto Validation Bot'
  ClientHeight = 146
  ClientWidth = 373
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
    Top = 127
    Width = 373
    Height = 19
    Panels = <>
    SimplePanel = True
    ExplicitTop = 160
  end
  object ButtonBotRun: TButton
    Left = 288
    Top = 96
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
  end
  object EditCpuzPath: TEdit
    Left = 104
    Top = 8
    Width = 178
    Height = 21
    TabOrder = 4
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
    Top = 100
    Width = 110
    Height = 17
    Caption = 'Ultra (no update)'
    TabOrder = 7
  end
  object EditFsbStep: TEdit
    Left = 104
    Top = 60
    Width = 33
    Height = 21
    NumbersOnly = True
    TabOrder = 8
    Text = '0'
  end
  object TimerBot: TTimer
    Enabled = False
    Interval = 6000
    OnTimer = TimerBotTimer
    Left = 128
    Top = 92
  end
  object OpenDialogBot: TOpenDialog
    DefaultExt = 'exe'
    Left = 176
    Top = 92
  end
end
