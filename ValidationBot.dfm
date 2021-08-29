object ValidationBotDialog: TValidationBotDialog
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsToolWindow
  Caption = 'Auto Validation Bot'
  ClientHeight = 179
  ClientWidth = 373
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
    Left = 11
    Top = 11
    Width = 68
    Height = 13
    Caption = 'Path to CPU-Z'
  end
  object Label2: TLabel
    Left = 11
    Top = 37
    Width = 72
    Height = 13
    Caption = 'Wait for CPU-Z'
  end
  object Label3: TLabel
    Left = 11
    Top = 63
    Width = 26
    Height = 13
    Caption = 'Sleep'
  end
  object Label4: TLabel
    Left = 175
    Top = 37
    Width = 13
    Height = 13
    Caption = 'ms'
  end
  object Label5: TLabel
    Left = 175
    Top = 63
    Width = 13
    Height = 13
    Caption = 'ms'
  end
  object Label6: TLabel
    Left = 224
    Top = 39
    Width = 58
    Height = 13
    Caption = 'Current FSB'
  end
  object Label7: TLabel
    Left = 222
    Top = 65
    Width = 60
    Height = 13
    Caption = 'Current CPU'
  end
  object Label8: TLabel
    Left = 11
    Top = 89
    Width = 46
    Height = 13
    Caption = 'Step'
  end
  object Label9: TLabel
    Left = 175
    Top = 90
    Width = 79
    Height = 13
    Caption = 'MHz (0 for auto)'
  end
  object StatusBarBot: TStatusBar
    Left = 0
    Top = 160
    Width = 373
    Height = 19
    Panels = <>
    SimplePanel = True
    ExplicitTop = 128
  end
  object ButtonBotRun: TButton
    Left = 288
    Top = 128
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
    Top = 60
    Width = 65
    Height = 21
    NumbersOnly = True
    TabOrder = 3
    Text = '6000'
  end
  object EditCpuzPath: TEdit
    Left = 104
    Top = 8
    Width = 178
    Height = 21
    TabOrder = 4
  end
  object EditCpuzWait: TEdit
    Left = 104
    Top = 34
    Width = 65
    Height = 21
    NumbersOnly = True
    TabOrder = 5
    Text = '10000'
  end
  object PanelCurrentFsb: TPanel
    Left = 288
    Top = 37
    Width = 75
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
  object EditCoreFrequency: TPanel
    Left = 288
    Top = 63
    Width = 75
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
    TabOrder = 7
  end
  object CheckBoxUltra: TCheckBox
    Left = 11
    Top = 132
    Width = 110
    Height = 17
    Caption = 'Ultra (no update)'
    TabOrder = 8
  end
  object EditFsbStep: TEdit
    Left = 104
    Top = 86
    Width = 65
    Height = 21
    NumbersOnly = True
    TabOrder = 9
    Text = '0'
  end
  object TimerBot: TTimer
    Enabled = False
    Interval = 6000
    OnTimer = TimerBotTimer
    Left = 104
    Top = 156
  end
  object OpenDialogBot: TOpenDialog
    DefaultExt = 'exe'
    Left = 152
    Top = 156
  end
end
