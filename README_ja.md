# 4-7セグさん kit

4-7セグさんは小数点付き4桁の7セグLEDつきの便利な基板です。
これを使うことで、BPMやレベルなど、数字を表示するマイコン工作が、簡単にできるようになります。

## 特徴

- LEDドライバを内蔵しているため、GPIO 2ピンのみで使用できます。
- 電源電圧、ロジックレベル変換を内蔵しているため、3.3V、5Vいずれのマイコンでも使用できます。
- ドライバIC(TM1640)用の[Arduinoライブラリ](./soft/4-7segs-san/TM1640.h)もあるので、簡単に使えます。

![](img/front.jpg)
![](img/back.jpg)
![](img/with_arduino.jpg)

## キットに含まれているもの

- Pre-assembled circuit board
- 組み立て済みの基板
- [カソードコモンLEDディスプレイ](https://www.lcsc.com/product-detail/_Shenzhen-Zhihao-Elec-_C54396.html)
- 1x4 ピンソケット

## 組みたてかた

1. はんだづけを簡単にするため、LEDディスプレイのピンを5mm程度にカットします。
2. LEDディスプレイと、ピンソケットをはんだづけします。

## サンプルプログラム

[soft/4-7segs-san](soft/4-7segs-san)にある例を参考にしてください。
