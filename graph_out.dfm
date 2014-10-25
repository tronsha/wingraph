object FormGraphOut: TFormGraphOut
  Left = 444
  Top = 98
  BorderIcons = []
  BorderStyle = bsNone
  BorderWidth = 4
  Caption = ' WinGraph'
  ClientHeight = 292
  ClientWidth = 292
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  DesignSize = (
    292
    292)
  PixelsPerInch = 96
  TextHeight = 13
  object PaintBox: TImage
    Left = 0
    Top = 0
    Width = 600
    Height = 600
    Anchors = [akLeft, akTop, akRight, akBottom]
    AutoSize = True
    Center = True
    Constraints.MaxHeight = 1000
    Constraints.MaxWidth = 1000
    OnMouseDown = PaintBoxMouseDown
    OnMouseMove = PaintBoxMouseMove
  end
end
