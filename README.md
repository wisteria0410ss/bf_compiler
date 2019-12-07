# Brainfuck Compiler
## これはなに
Brainfuck のコンパイラ

Brainfuck のコードを読み込んで GAS_Intel 記法のアセンブリや、
x86_64 で Linux な環境で動く実行可能ファイルを吐き出します。

## ビルド
適当なディレクトリで次のコマンドを実行します。
```bash
$ git clone https://github.com/wisteria0410ss/bf_compiler
$ cd ./bf_compiler/
$ mkdir bin obj
$ make
```
- `gcc`が必要です
- `bin/bfc` ができるはずです

## 使い方
```
bfc [-S] [-o outfile] infile
```
- **-S**
    - GAS_Intel 記法のアセンブリを出力します
    - 省略した場合、実行可能ファイルが出力されます
- **-o** *outfile*
    - `outfile`に結果を出力します
    - 省略した場合、標準出力に結果が出力されます
- *infile*
    - 処理するファイルを指定します
    - 複数ファイルの指定はできません
    - 省略した場合、標準入力から読み込むことを試みます
