object frmMain: TfrmMain
  Left = 0
  Top = 0
  Caption = #1053#1072#1079#1074#1072#1085#1080#1077' '#1087#1088#1086#1075#1080
  ClientHeight = 165
  ClientWidth = 359
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  Visible = True
  PixelsPerInch = 96
  TextHeight = 13
  object btnExit: TBitBtn
    Left = 276
    Top = 132
    Width = 75
    Height = 25
    Caption = #1042#1099#1093#1086#1076
    DoubleBuffered = True
    ParentDoubleBuffered = False
    TabOrder = 2
    OnClick = btnExitClick
  end
  object btnCompress: TButton
    Left = 251
    Top = 8
    Width = 100
    Height = 25
    Caption = 'Compress file'
    TabOrder = 0
    OnClick = btnCompressClick
  end
  object btnDecompress: TButton
    Left = 251
    Top = 37
    Width = 100
    Height = 25
    Caption = 'Decompress file'
    TabOrder = 1
    OnClick = btnDecompressClick
  end
end
