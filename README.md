3D DXlib 

「SpringFairy」

～概要～

言語:C++

制作期間:2か月

ジャンル:ファンタジック・シューティングゲーム


～力を入れているポイント～

キャラクターの魅力を最大限引き出すための様々な演出を盛り込んでいます。
今後も拡張予定です。

～実装上の苦労したところ～

3D作品としての利点を最大限活かし、プログラマーとしてキャラクターの魅力をどのように引き出せるかを考えた時、
行列計算によるモデルの回転やカメラワークなど、3D作品を制作するにあたって基礎となる知識が必須と考えました。

直観的な感覚だけで上下左右を定義していた2Dとは異なり、
空間を意識して、どの方向へ動きそのために向くべき方向を算出し、微調整を加えていく中で、
ある程度の基礎的な考え方は構築されつつあります。

尚、アルゴリズムとして、自動経路による座標移動はA*を用いています。
前後左右の四方向だけではなく、3Dなので斜めも導入した全８方向で管理しています。

～今後の展望～

キャラクターの魅力を引き出すための仕掛けは、まだまだ足りていない、もっと魅力を引き出す方法はあると常に考えています。
せっかくご覧いただける機会なので、審査会では、そういった「もっと魅力を引き出すためのアドバイス」もいただけましたら幸いです。

～コードについて～

製作途中ということもあり、コメント無しやマジックナンバーなど、
好ましくない形態になってしまっております。
こちらは作品が一度完成しましたら、デバッグを取るなど行いながら調整していく予定です。
※現状では、ひとまずは完成させることを第一に制作しております。

～リポジトリの補足～

当初はSpringFairy001のリポジトリにて作業をしておりましたが、データ移行に伴い、
リポジトリも002番を新たに作成しました。（001番でのプッシュ回数は80回ほどです）
001についてはアセットデータが内蔵されているため、現状private非公開となっておりますが、ご希望であれば公開に変更いたします。

また、今後のチーム制作でのGit操作にも慣れるため、マージなども独自で練習しながら進めております。

～アセットの著作権について～

今回、アセットのデータ再配布防止のため、アセットデータは削除した上での提出となります。
作品としての動作は十分に確認できない状態でありますので、コードのみご覧いただければと思います。
