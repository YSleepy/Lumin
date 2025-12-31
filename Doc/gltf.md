```
tinygltf::Model 包含以下关键成员（均为 std::vector）：

accessors：描述如何读取 buffer 数据（如顶点位置、法线等）
buffers：原始二进制数据
bufferViews：buffer 的视图（指定偏移、长度、stride 等）
meshes：网格列表，每个包含多个 primitives（图元）
primitives：包含 attributes（如 POSITION, NORMAL, TEXCOORD_0）和 indices
materials：材质信息（PBR、颜色、纹理等）
textures, images, samplers：纹理相关数据

```

`buffers`
```
buffers 是 std::vector<tinygltf::Buffer>，每个 Buffer 对象包含一段原始二进制数据（std::vector<unsigned char> data）。
一个 glTF 文件（.gltf + .bin 或内嵌在 .glb 中）的所有几何、动画、皮肤权重等数据最终都存放在 buffers 里。
```

`bufferViews`

```
bufferViews 是 std::vector<tinygltf::BufferView>。
每个 BufferView 表示对某个 buffer 的一个子区域（subrange），并附加了元数据，如：
buffer：引用的 buffer 索引（bufferViews[i].buffer）
byteOffset：从 buffer 开头偏移多少字节开始
byteLength：这个视图有多长（字节数）
byteStride：每个元素（如每个顶点）占多少字节（可选，0 表示紧凑排列）
target：用途（如 GL_ARRAY_BUFFER 表示顶点数据，GL_ELEMENT_ARRAY_BUFFER 表示索引数据）

bufferView 告诉你：“从 buffer 的哪个位置开始、读多少字节、每个元素多宽”。
```

`accessors`

```
accessors 是 std::vector<tinygltf::Accessor>。
每个 Accessor 描述如何解释 bufferView 中的数据，包括：
bufferView：引用的 bufferView 索引
byteOffset：在 bufferView 内部的额外偏移（常用于对齐）
count：元素个数（如顶点数）
type：数据类型（如 VEC3、SCALAR、MAT4）
componentType：每个分量的数据类型（如 FLOAT、UNSIGNED_SHORT、UNSIGNED_BYTE）
可选：min / max（边界框用）、normalized（是否归一化）

```
