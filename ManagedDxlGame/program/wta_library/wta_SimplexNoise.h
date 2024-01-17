#pragma once
#include "../dxlib_ext/dxlib_ext.h"


namespace wta
{
	// 勾配ベクトルのセットを定義
	static const int grad3[12][3] =
	{
		{1,1,0}, {-1,1,0}, {1,-1,0}, {-1,-1,0},
		{1,0,1}, {-1,0,1}, {1,0,-1}, {-1,0,-1},
		{0,1,1}, {0,-1,1}, {0,1,-1}, {0,-1,-1}
	};

	// フェード関数(イメージ : 山々の山間の繋がりの滑らかさ)
	// args ... 1次元の座標
	// return ... 0.0f ~ 1.0f の値
	// ex ... float fade = wta::SimplexNoise::fade(x);
	inline float fade(float t)
	{
		// 数学的に導かれた計算式でなく、望ましい結果を得るため実験的に決定
		// 各数値はノイズ生成のための定数として考えていい
		// 変更すれば生成の度合も変わる
		return t * t * t * (t * (t * 6 - 15) + 10);
	}

	// 補間関数（イメージ : ひとつの山の斜面の滑らかさ）
	// args1 ... 補間の始点
	// args2 ... 補間の終点 
	// args3 ... 補間係数
	// return ... -1.0f ~ 1.0f の値
	// ex ... float lerp = wta::SimplexNoise::lerp(x, y);
	inline float lerp(float a, float b, float t)
	{
		// 補間のために中間の値を計算
		// 線形補間（ノイズ生成の一環として値間の滑らかな遷移）
		// b - a : 始点と終点の差分
		// t * (b - a) : 補間係数を乗算して補間距離を計算
		// a + t * (b - a) : 始点に補間距離を加算して補間結果を計算
		return a + t * (b - a);
	}

	// 3次元の座標に対するハッシュ関数
	// ノイズ生成のため（ランダム値）
	// ハッシュ : 任意の数値を、一定のルールに基づいて固定長の値に変換
	// 今回は、3次元の座標をハッシュ関数に入れて、ランダムな値を生成
	// args ... 3次元の座標
	// return ... 0 ~ 255 の値
	// ex ... int hash =　wta::SimplexNoise::hash(x, y, z);
	inline int hash(float x, float y, float z)
	{
		// 57 : 1次元のハッシュ関数の素数
		// 3623 : 2次元のハッシュ関数の素数
		// 160621 : 3次元のハッシュ関数の素数
		// これらの数値は、ランダムな値を生成するための素数
		int n = static_cast<int>(x + y * 57 + z * 3623);
		// ビットシフト演算
		// これにより、ランダムな値を生成
		// 13 : 1次元のハッシュ関数のシフト数
		// 7 : 2次元のハッシュ関数のシフト数
		// 11 : 3次元のハッシュ関数のシフト数
		// n のビットを左に11ビットシフト
		// 実質的に数値を2のシフト回数分の累乗で乗算することと等価
		// この場合は 2 ^ 11(2進数でのシフト演算のため)
		// 元の数値 n のビットパターンが変化し、ハッシュ関数のランダム性が増す
		n = (n << 11) ^ n;
		// これにより、ランダムな値を生成
		// 15731 : 1次元のハッシュ関数の素数
		// 789221 : 2次元のハッシュ関数の素数
		// 1376312589 : 3次元のハッシュ関数の素数
		// & : ビット演算のAND
		// 0x7fffffff : 32bitの最大値
		// これらの数値は、ランダムな値を生成するための素数
		// 符号なし整数にするために、ビット演算を行う
		return (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff;
	}

	// ノイズ生成のための勾配ベクトルを生成する関数(3次元用)
	// ハッシュ値を基に勾配ベクトルを生成
	// ノイズの各点において方向性を持たせる
	// args1 ... ハッシュ値(ノイズ生成のために使用)
	// args2~4 ... 3次元の座標
	// return ... -1.0f ~ 1.0f の値
	// ex ... float grad = wta::SimplexNoise::grad(hash,x,y,z);
	inline float grad(int hash, float x, float y, float z)
	{
		// ハッシュ値に対してビットAND演算を行う
		// 15 : 2進数で 1111
		// ハッシュ値の下4桁を取得（0~15の範囲に制限）
		// AND演算により、ハッシュ値の下4桁以外のビットは0になる
		// 次にどの勾配ベクトルを使うかを決定するために、ハッシュ値の下4桁を取得
		// ex ) 101101110011(ハッシュ値)
		// AND  000000000111(15)
		// ------------------
		//      000000000011(3) : 下4桁のみ残る
		// 下4桁の値は、勾配ベクトル選択で限定された範囲のインデックスを得るため
		// 勾配ベクトルのセットが12であるため、下4桁の値をその範囲に収めたい
		// 下4桁を使用すると、得られる値を0~15の範囲に制限できる
		// ☆3次元シンプレックスの実装では12個の勾配ベクトルを使用するのが一般的
		// 12個の勾配ベクトルは、3次元空間を正四面体の形状（5つ）に分割したとき
		// 各正四面体の頂点に12個の異なる勾配ベクトルを割り当てる
		// これにより、生成されるノイズが空間全体に均一に分布
		// 各頂点の勾配ベクトルは、その点でのノイズに方向性と強度を決定
		// 三次元格子 : 互いに隣接する格子点（グリッドポイント）で構成
		// 各頂点から出発し、その周囲の空間をカバーするために正四面体を配置
		// 1つの格子点に対して、その点を含む正四面体は合計5つ存在する
		// その格子点とその近隣の点から構成される空間をカバーするため
		int h = hash & 15;
		// u < 8　ならxを使用し、そうでなければyを使用
		// h : 上記で取得した下4桁の値（0~15の範囲）
		// 8 ; 0~15の中央値（ランダム性、均等な分布、簡易な計算を実現）
		// ハッシュ値に基づいて勾配ベクトルの一部を選択
		// ハッシュ値によって、xまたはyのどちらを使用するかを決定する
		// 3次元ノイズにおける勾配ベクトルの方向性をランダム化し、
		// ノイズパターンに多様性を持たせる
		// 現時点では z座標をまだ考慮しない
		// z座標を考慮すると、ノイズパターンが縦方向に伸びてしまうため
		// uは勾配ベクトルの一部として、xyいずれか一方の方向性を捉えるために使用
		float u = h < 8 ? x : y;
		// 式自体は
		// if (h < 4) {v = y;}
		// else 
		// {
		//		if (h == 12 || h == 14) { v = x;}
		//		else { v = z;}
		//	}
		// 条件に基づいて、x,y,zのどれを使用するかを決定
		// 3次元ノイズにおける勾配ベクトルの方向性をランダム化するために使用
		// 4 : ハッシュ値が0~15(16個の要素)の場合、4で分ける方法が効果的(場合による)
		// 4で分けることで、ノイズパターンに多様性を持たせる
		// 12 : 3次元では12個の勾配ベクトルを一般的に使用する
		// 12個の勾配ベクトルは、3次元空間を正四面体の形状（5つ）に分割したとき
		// 各正四面体の頂点に12個の異なる勾配ベクトルを割り当てる
		// 14 : ランダム性、均等な分布、簡易な計算を実現するための任意の数字
		// 必ずしも14でなくてもよい（適してなければ適宜変更してもよい）
		// 一般的には、今回の条件では14が最適なだけで、最善ではない
		// 今回と同じ条件でも他の式を用いることで、パターンを変化することも可能
		// ex ) h < 5 ? x : h < 10 : y : z;
		//		(h % 3 == 0) ? x : (h % 3 == 1) ? y : z;
		//		(h % 6 < 2 ) ? x : (h % 6 < 4) ? y : z;
		// この式を用いたのは、ランダム性、均等な分布、簡易な計算を実現するため
		// 条件式が比較的シンプルで、計算効率を維持できる(最適であり最善ではない)
		float v = h < 4 ? y : h == 12 || h == 14 ? x : z;
		// 特定の点での勾配ベクトルを算出
		// h & 1 : ビットAND演算(&)により、最下位ビットが0か1かを判定(00001)
		// h & 2 : ビットAND演算(&)により、下から2番目のビットを判定(00010)
		// これらのビットの値によって、勾配ベクトルの正負を決定
		// 正の値なら普通の山、負の値なら逆さ山
		// 今回はuとvの二つの要素の加算だが、より精巧にするためwを加算することも
		// あくまで簡易的な計算で実装するため、今回はuとvの二つの要素を加算
		// ただし三次元の場合、最大要素数は3つまで
		return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
	}
	// 3次元のシンプレックスノイズを計算する関数
	float Calculate3DSimplexNoise(tnl::Vector3 pos)
	{
		// 3次元のシンプレックスノイズの計算は、2次元の計算と同じ
		// 3次元の場合は、3つの頂点の勾配ベクトルを計算

		// 勾配ベクトルの計算
		// floor : 与えられた引数の値以下の最大の整数を返す(小数点切り捨て)
		// 特定の点の座標を整数の格子点にマッピングするため
		// 格子点 : 次元空間内において一定間隔で配置された点
		// ノイズ生成において空間を構造化し、各点のノイズ値を計算するために使用
		// ノイズ値の算出で、周囲の格子点に割り当てられた勾配ベクトルを使用するため
		int ix = (int)floor(pos.x);
		int iy = (int)floor(pos.y);
		int iz = (int)floor(pos.z);
		// 小数点以下の値のみ取得
		// 格子点からどの位離れているかを表す
		// ノイズ値算出で、関連する格子点に割り当てられた勾配ベクトルを使用するため
		float fx = pos.x - ix;
		float fy = pos.y - iy;
		float fz = pos.z - iz;

		// フェード関数を適用
		// 隣接する格子点間のノイズ値の遷移を滑らかにする
		// ノイズパターン全体に対してより滑らかで連続的な外観を実現
		float u = fade(fx);
		float v = fade(fy);
		float w = fade(fz);

		// ハッシュ関数を使って勾配ベクトルを生成
		// 特定の点の周囲にある隣接する格子点のハッシュ値を算出
		// +1 : その点に最も近い隣接する格子点の座標を算出できる
		// これにより、その点の周囲にある隣接する格子点のハッシュ値を算出
		// +1によって算出される格子点は、元の点の直接的な隣接空間をカバーする。
		// これにより、空間の連続性とノイズの滑らかさを保持
		// -1や+2などの値を使用すると、ノイズの滑らかさが失われる
		// 特に-1だと、指定された点と異なる空間的関係を持つ格子点を算出される
		float h0 = hash(ix, iy, iz);
		float h1 = hash(ix + 1, iy, iz);
		float h2 = hash(ix, iy + 1, iz);
		float h3 = hash(ix + 1, iy + 1, iz);
		float h4 = hash(ix, iy, iz + 1);
		float h5 = hash(ix + 1, iy, iz + 1);
		float h6 = hash(ix, iy + 1, iz + 1);
		float h7 = hash(ix + 1, iy + 1, iz + 1);

		// それぞれの頂点の勾配ベクトルを計算
		// +1 : 特定の点の周囲にある格子点を選択するため
		// -1 : これらの格子点と元の点の相対位置を計算するため
		tnl::Vector3 g0 = { grad(h0, fx, fy, fz)
							, grad(h0, fx, fy, fz)
							, grad(h0, fx, fy, fz) };

		tnl::Vector3 g1 = { grad(h1, fx - 1, fy, fz)
							, grad(h1, fx - 1, fy, fz)
							, grad(h1, fx - 1, fy, fz) };

		tnl::Vector3 g2 = { grad(h2, fx, fy - 1, fz)
							, grad(h2, fx, fy - 1, fz)
							, grad(h2, fx, fy - 1, fz) };

		tnl::Vector3 g3 = { grad(h3, fx - 1, fy - 1, fz)
							, grad(h3, fx - 1, fy - 1, fz)
							, grad(h3, fx - 1, fy - 1, fz) };

		tnl::Vector3 g4 = { grad(h4, fx, fy, fz - 1)
							, grad(h4, fx, fy, fz - 1)
							, grad(h4, fx, fy, fz - 1) };

		tnl::Vector3 g5 = { grad(h5, fx - 1, fy, fz - 1)
							, grad(h5, fx - 1, fy, fz - 1)
							, grad(h5, fx - 1, fy, fz - 1) };

		tnl::Vector3 g6 = { grad(h6, fx, fy - 1, fz - 1)
							, grad(h6, fx, fy - 1, fz - 1)
							, grad(h6, fx, fy - 1, fz - 1) };

		tnl::Vector3 g7 = { grad(h7, fx - 1, fy - 1, fz - 1)
							, grad(h7, fx - 1, fy - 1, fz - 1)
							, grad(h7, fx - 1, fy - 1, fz - 1) };

		// 重みを計算（特定の点が各格子点からどの程度離れているか考慮）
		// ノイズの滑らかな遷移を実現するために使用
		// 特定の点の周囲に隣接する格子点間からの寄与（重み）を算出（山間の波）
		// w0 : 点がix,iy,izに最も近い場合に最も大きくなる	
		// 点が ix に非常に近い場合、u は小さくなり、1 - u は大きくなる
		// これは、点がその格子点からの影響を強く受けることを意味する
		float w0 = (1 - u) * (1 - v) * (1 - w);
		// w1 : 点がix+1,iy,izに最も近い場合に最も大きくなる
		float w1 = u * (1 - v) * (1 - w);
		float w2 = (1 - u) * v * (1 - w);
		float w3 = u * v * (1 - w);
		float w4 = (1 - u) * (1 - v) * w;
		float w5 = u * (1 - v) * w;
		float w6 = (1 - u) * v * w;
		float w7 = u * v * w;

		// それぞれの頂点の値を計算
		// 内積（ドット積）は、2つのベクトル間の方向性の関係を数値化する
		// 特定の点の勾配ベクトルの方向と、その点の格子点からの相対位置を評価
		// 点が g0 が示す方向にどれだけ寄与するかを算出
		// 値が大きいほど、勾配ベクトルと相対位置ベクトルの方向が一致し影響が強い
		// ノイズパターンに方向性と強度が与えられ、リアルで滑らかなテクスチャを生成
		float n0 = tnl::Vector3::Dot(g0, { fx, fy, fz });
		float n1 = tnl::Vector3::Dot(g1, { fx - 1, fy, fz });
		float n2 = tnl::Vector3::Dot(g2, { fx, fy - 1, fz });
		float n3 = tnl::Vector3::Dot(g3, { fx - 1, fy - 1, fz });
		float n4 = tnl::Vector3::Dot(g4, { fx, fy, fz - 1 });
		float n5 = tnl::Vector3::Dot(g5, { fx - 1, fy, fz - 1 });
		float n6 = tnl::Vector3::Dot(g6, { fx, fy - 1, fz - 1 });
		float n7 = tnl::Vector3::Dot(g7, { fx - 1, fy - 1, fz - 1 });

		// 補間関数を適用して、最終的なノイズ値を計算
		// 最終的なノイズ値算出で、複数の線形補間を組み合わせて使用
		// 初期補間 : 隣接する格子点から得られたノイズ値（n0,n1,n2,n3など）を
		//			　補間係数 u, v, w を用いて線形補間
		// 中間補間 : 初期補間結果を更に組み合わせて、次の次元に沿って補間
		// 最終補間 : 中間補間結果を w を用いて補間し
		//			　特定の点における最終的なノイズ値を生成
		float noise = lerp(lerp(lerp(n0, n1, u)
					, lerp(n2, n3, u), v)
					, lerp(lerp(n4, n5, u)
					, lerp(n6, n7, u), v), w);

		return noise;
	}

	// 3次元
	// arg1 ... 3次元の座標(この点に対してノイズ値を計算)
	// arg2 ... 周波数(ノイズパターンの細かさや粗さを調節)
	// arg3 ... 振幅(ノイズに複数の周波数成分を追加し、より複雑なパターンを生成)
	// arg4 ... 各オクターブの振幅の減衰率(高くなる度、周波数はこの係数によって減少)
	// arg5 ... 各オクターブの周波数の増加率(高くなる度、周波数はこの係数によって増加)
	// arg6 ... オフセット(ノイズ値の範囲を調整)
	// return ... -1.0f ~ 1.0f の値
	float SimplexNoise3D(tnl::Vector3 pos
						, float scale = 1.0f
						, int octaves = 1
						, float persistence = 0.5f
						, float lacunarity = 2.0f
						, float offset = 0.0f)
	{
		// 累積されるノイズ値
		float total = 0.0f;
		// 周波数
		float frequency = scale;
		// 振幅
		float amplitude = 1.0f;
		// 最大値(正規化のために使用される最大値を累積)
		float max_value = 0.0f;

		for (int i = 0; i < octaves; i++)
		{
			// スケーリングされた座標を算出
			// スケーリング : 座標を変換することで、ノイズの細かさや粗さを調節
			float nx = pos.x * frequency / 100.0f;
			float ny = pos.y * frequency / 100.0f;
			float nz = pos.z * frequency / 100.0f;

			// ここで3Dシンプレックスノイズの計算を行う
			float noise_value = Calculate3DSimplexNoise({ nx, ny, nz });
			// オクターブのノイズ値に対応する振幅を乗算し、累積ノイズ値に加算
			// 振幅 : ノイズに複数の周波数成分を追加し、より複雑なパターンを生成
			total += noise_value * amplitude;
			// 正規化のために使用される最大値を振幅の合計で更新
			// 最終的なノイズ値が所定の範囲内(-1.0f ~ 1.0f)に収まるようにするため
			max_value += amplitude;
			// 振幅は各オクターブで減衰
			// より高いオクターブではノイズの影響が小さくなり、細かい詳細が生成
			amplitude *= persistence;
			// 周波数増加は、より高いオクターブでのノイズ成分のスケールを小さくする
			// より高いオクターブではノイズの影響が小さくなり、細かい詳細が生成
			frequency *= lacunarity;
		}
		// 累積されたノイズ値を最大値で割って正規化
		// これにより、ノイズ値の範囲が -1.0f ~ 1.0f になる
		return total / max_value + offset;
	}
}

