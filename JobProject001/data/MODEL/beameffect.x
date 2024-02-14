xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 22;
 28.70569;32.38662;1.07133;,
 20.28797;12.06447;1.07133;,
 20.28792;12.06447;-321.75830;,
 28.70565;32.38662;-321.75830;,
 -0.03419;3.64673;1.07121;,
 -0.03423;3.64673;-321.75830;,
 -20.35631;12.06447;1.07133;,
 -20.35635;12.06447;-321.75830;,
 -0.03423;3.64673;-321.75830;,
 -28.77401;32.38662;1.07133;,
 -28.77405;32.38663;-321.75830;,
 -20.35631;52.70876;1.07133;,
 -20.35635;52.70877;-321.75830;,
 -0.03419;61.12652;1.07133;,
 -0.03423;61.12652;-321.75818;,
 20.28797;52.70876;1.07133;,
 20.28792;52.70876;-321.75830;,
 -0.03419;32.38662;1.07133;,
 -0.03423;32.38662;-321.75830;,
 28.70565;32.38662;-321.75830;,
 20.28792;12.06447;-321.75830;,
 20.28792;52.70876;-321.75830;;
 
 24;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,8;,
 4;6,9,10,7;,
 4;9,11,12,10;,
 4;11,13,14,12;,
 4;13,15,16,14;,
 4;15,0,3,16;,
 3;17,1,0;,
 3;17,4,1;,
 3;17,6,4;,
 3;17,9,6;,
 3;17,11,9;,
 3;17,13,11;,
 3;17,15,13;,
 3;17,0,15;,
 3;18,19,20;,
 3;18,20,8;,
 3;18,8,7;,
 3;18,7,10;,
 3;18,10,12;,
 3;18,12,14;,
 3;18,14,21;,
 3;18,21,19;;
 
 MeshMaterialList {
  1;
  24;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.540000;0.540000;0.540000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   1.000000;1.000000;1.000000;;
   TextureFilename {
    "data\\TEXTURE\\Beam001.jpg";
   }
  }
 }
 MeshNormals {
  18;
  0.000000;-0.000001;1.000000;,
  1.000000;0.000000;-0.000000;,
  0.707107;-0.707107;-0.000000;,
  -0.000000;-1.000000;-0.000000;,
  -0.707108;-0.707106;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.707108;0.707106;0.000000;,
  -0.000000;1.000000;0.000000;,
  0.707107;0.707106;-0.000000;,
  0.000000;0.000001;-1.000000;,
  -0.000002;-0.000002;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.000004;1.000000;,
  0.000002;-0.000002;1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000002;0.000002;-1.000000;,
  0.000000;0.000004;-1.000000;,
  -0.000002;0.000002;-1.000000;;
  24;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,1,1,8;,
  3;0,10,11;,
  3;0,12,10;,
  3;0,13,12;,
  3;0,11,13;,
  3;0,11,11;,
  3;0,11,11;,
  3;0,11,11;,
  3;0,11,11;,
  3;9,14,14;,
  3;9,14,14;,
  3;9,14,14;,
  3;9,14,14;,
  3;9,14,15;,
  3;9,15,16;,
  3;9,16,17;,
  3;9,17,14;;
 }
 MeshTextureCoords {
  22;
  0.471135;0.449077;,
  0.479487;0.706014;,
  0.019322;0.706014;,
  0.027206;0.449077;,
  0.500035;0.812441;,
  -0.000033;0.812441;,
  0.520581;0.706014;,
  0.980614;0.706014;,
  0.999967;0.812441;,
  0.528932;0.449077;,
  0.972731;0.449077;,
  0.520581;0.192140;,
  0.980614;0.192140;,
  0.500035;0.085713;,
  0.999967;0.085713;,
  0.479487;0.192140;,
  0.019322;0.192140;,
  0.500035;0.449077;,
  0.999967;0.449077;,
  1.027206;0.449077;,
  1.019322;0.706014;,
  1.019322;0.192140;;
 }
}
