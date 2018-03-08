# SymmetricalFace

## 概要
OpenCVを利用して顔を認識し、顔の左側、右側それぞれの左右対称顔を表示するプログラムです。

## 開発環境
* OpenCV 3.4.0
* Visual Studio 2015

## OpenCV を Visual Studio から使用するときの設定
[OpenCV 3.4.1をVisual Studio 2017から使用する時の手順](https://qiita.com/h-adachi/items/aad3401b8900438b2acd)そのままです。

1. OpenCVをインストール  
[OpenCV](https://github.com/opencv/opencv/releases)をダウンロードし、任意のフォルダに展開する。 (展開したPATHを "%OPENCV%" とする)

2. プロジェクトを作成  
ファイル -> 新規作成 -> プロジェクト -> Visual C++ -> Windows コンソールアプリケーション から、「空のプロジェクト」を作成する。

3. 各種設定を行う  
* ビルド -> 構成マネージャー で、 「Debug / Release」、 「x64 / x86」 を選択する。
* プロジェクト -> ～のプロパティ  
|設定内容|値|
----|---- 
|構成プロパティ - デバック - 環境 |PATH=%OPENCV%\build\x64\vc15\bin;%PATH%|
|構成プロパティ - C/C++ - 追加のインクルードディレクトリ|%OPENCV%\build\include|
|構成プロパティ - リンカー - 追加のライブラリディレクトリ|%OPENCV%\build\x64\vc15\lib|
|構成プロパティ - リンカー - 入力 - 追加の依存ファイル|opencv_world341d.lib or opencv_world341.lib|
を設定する。

## 今後の課題
画素ごとに書き換えているのでとても非効率な感じがします。  
もっとうまいやり方あると思う...
