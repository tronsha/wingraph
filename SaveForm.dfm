object FormSave: TFormSave
  Left = 666
  Top = 809
  BorderIcons = [biSystemMenu]
  BorderStyle = bsNone
  Caption = ' Speichern'
  ClientHeight = 65
  ClientWidth = 224
  Color = clBlack
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenuSave
  OldCreateOrder = False
  Position = poMainFormCenter
  OnDeactivate = FormDeactivate
  PixelsPerInch = 96
  TextHeight = 13
  object LabelSave: TLabel
    Left = 170
    Top = 4
    Width = 35
    Height = 22
    Caption = '.png'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWhite
    Font.Height = -19
    Font.Name = 'Times New Roman'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object ButtonSave: TButton
    Left = 25
    Top = 32
    Width = 75
    Height = 25
    Caption = 'Speichern'
    TabOrder = 1
    OnClick = ButtonSaveClick
  end
  object EditSave: TEdit
    Left = 15
    Top = 4
    Width = 150
    Height = 21
    TabOrder = 0
    OnKeyPress = EditSaveKeyPress
  end
  object ButtonCancel: TButton
    Left = 125
    Top = 32
    Width = 75
    Height = 25
    Caption = 'Abbrechen'
    TabOrder = 2
    OnClick = ButtonCancelClick
  end
  object MainMenuSave: TMainMenu
    Top = 32
    object MenuSavePNG: TMenuItem
      Caption = 'PNG'
      OnClick = MenuSavePNGClick
    end
    object MenuSaveBMP: TMenuItem
      Caption = 'BMP'
      OnClick = MenuSaveBMPClick
    end
    object MenuSaveGIF: TMenuItem
      Caption = 'GIF'
      OnClick = MenuSaveGIFClick
    end
    object MenuSaveTIFF: TMenuItem
      Caption = 'TIF'
      OnClick = MenuSaveTIFFClick
    end
    object MenuSaveJPEG: TMenuItem
      Caption = 'JPG'
      OnClick = MenuSaveJPEGClick
    end
  end
end
