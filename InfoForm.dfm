object FormInfo: TFormInfo
  Left = 200
  Top = 215
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Info '#252'ber WinGraph'
  ClientHeight = 197
  ClientWidth = 302
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnCreate = FormCreate
  OnDeactivate = FormDeactivate
  DesignSize = (
    302
    197)
  PixelsPerInch = 96
  TextHeight = 13
  object LabelInfoName: TLabel
    Left = 31
    Top = 8
    Width = 235
    Height = 64
    Caption = 'WinGraph'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -56
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object LabelInfoCopyright: TLabel
    Left = 31
    Top = 83
    Width = 57
    Height = 15
    Anchors = [akBottom]
    Caption = 'Copyright:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object LabelInfoHomepage: TLabel
    Left = 31
    Top = 99
    Width = 60
    Height = 15
    Anchors = [akBottom]
    Caption = 'Homepage:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object LabelInfoVersion: TLabel
    Left = 31
    Top = 131
    Width = 44
    Height = 15
    Anchors = [akBottom]
    Caption = 'Version:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object LabelInfoCopyrightText: TLabel
    Left = 100
    Top = 83
    Width = 91
    Height = 15
    Anchors = [akBottom]
    Caption = #169' Stefan H'#252'sges'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object LabelInfoHomepageText: TLabel
    Left = 100
    Top = 99
    Width = 112
    Height = 15
    Cursor = crHandPoint
    Anchors = [akBottom]
    Caption = 'http://www.mpcx.net'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -13
    Font.Name = 'Times New Roman'
    Font.Style = [fsItalic, fsUnderline]
    ParentFont = False
    OnClick = LabelInfoHomepageTextClick
  end
  object LabelInfoVersionText: TLabel
    Left = 100
    Top = 131
    Width = 24
    Height = 15
    Anchors = [akBottom]
    Caption = '2.5.2'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object LabelInfoSource: TLabel
    Left = 31
    Top = 115
    Width = 40
    Height = 15
    Anchors = [akBottom]
    Caption = 'Source:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object LabelInfoSourceText: TLabel
    Left = 100
    Top = 115
    Width = 203
    Height = 15
    Cursor = crHandPoint
    Anchors = [akBottom]
    Caption = 'https://github.com/tronsha/wingraph'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -13
    Font.Name = 'Times New Roman'
    Font.Style = [fsItalic, fsUnderline]
    ParentFont = False
    OnClick = LabelInfoSourceTextClick
  end
  object ButtonOK: TButton
    Left = 114
    Top = 163
    Width = 75
    Height = 25
    Anchors = [akBottom]
    Caption = 'OK'
    TabOrder = 0
    OnClick = ButtonOKClick
    ExplicitTop = 147
  end
end
