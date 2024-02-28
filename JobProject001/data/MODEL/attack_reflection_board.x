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
 111;
 -100.00000;53.87780;-4.63140;,
 100.00000;53.87780;-4.63140;,
 100.00000;-53.87780;-4.63140;,
 -100.00000;-53.87780;-4.63140;,
 100.00000;53.87780;-4.63140;,
 100.00000;53.87780;4.63140;,
 100.00000;-53.87780;4.63140;,
 100.00000;-53.87780;-4.63140;,
 100.00000;53.87780;4.63140;,
 -100.00000;53.87780;4.63140;,
 -100.00000;-53.87780;4.63140;,
 100.00000;-53.87780;4.63140;,
 -100.00000;53.87780;4.63140;,
 -100.00000;53.87780;-4.63140;,
 -100.00000;-53.87780;-4.63140;,
 -100.00000;-53.87780;4.63140;,
 100.00000;53.87780;-4.63140;,
 -100.00000;53.87780;-4.63140;,
 -100.00000;-53.87780;-4.63140;,
 100.00000;-53.87780;-4.63140;,
 85.00000;-49.25000;-7.04000;,
 91.41370;-49.25160;-7.03890;,
 91.41370;-49.25160;1.42850;,
 85.00000;-49.25000;1.42890;,
 85.00000;49.25160;-7.03920;,
 85.00000;49.25330;1.42890;,
 91.41370;49.25160;1.42850;,
 91.41370;49.25160;-7.03890;,
 -85.00000;49.25000;-7.03850;,
 -91.41370;49.25160;-7.03890;,
 -91.41370;49.25160;1.42850;,
 -85.00000;49.25000;1.42890;,
 0.00000;49.25160;1.42850;,
 85.00000;49.25160;-7.03920;,
 -85.00000;-49.25330;-7.03850;,
 85.00000;-49.25000;-7.04000;,
 0.00000;-49.25160;1.42850;,
 -85.00000;-49.25330;1.42890;,
 -91.41370;-49.25160;1.42850;,
 -91.41370;-49.25160;-7.03890;,
 85.00000;40.00000;-5.58000;,
 85.00000;-40.00000;-5.47000;,
 -85.00000;-40.00000;-5.58000;,
 -85.00000;39.99840;-5.58140;,
 85.00000;40.00000;-5.58000;,
 -85.00000;39.99840;-5.58140;,
 -85.00000;49.25000;-7.03850;,
 85.00000;49.25160;-7.03920;,
 85.00000;40.00000;-5.58000;,
 85.00000;49.25160;-7.03920;,
 91.41370;49.25160;-7.03890;,
 91.41370;40.00000;-7.03850;,
 91.41000;-40.00000;-7.04000;,
 85.00000;-40.00000;-5.47000;,
 -85.00000;-40.00000;-5.58000;,
 -91.41000;-40.00000;-7.04000;,
 -91.41370;40.00000;-7.03850;,
 -91.41370;49.25160;-7.03890;,
 91.41370;40.00000;-7.03850;,
 91.41370;49.25160;-7.03890;,
 91.41370;40.00000;1.42890;,
 91.41370;0.00000;1.42850;,
 91.41000;-40.00000;-7.04000;,
 -91.41370;40.00000;-7.03850;,
 -91.41000;-40.00000;-7.04000;,
 -91.41370;0.00000;1.42850;,
 -91.41370;40.00000;1.42890;,
 -91.41370;49.25160;-7.03890;,
 91.41370;40.00000;1.42890;,
 91.41370;49.25160;1.42850;,
 85.00000;49.25330;1.42890;,
 85.00000;40.00160;1.42930;,
 85.00000;0.00160;1.42890;,
 91.41370;0.00000;1.42850;,
 -91.41370;40.00000;1.42890;,
 -91.41370;0.00000;1.42850;,
 -85.00000;-0.00160;1.42890;,
 -85.00000;39.99840;1.42930;,
 -85.00000;49.25000;1.42890;,
 -91.41370;49.25160;1.42850;,
 0.00000;40.00000;1.42890;,
 0.00000;0.00000;1.42850;,
 85.00000;-40.00000;-5.47000;,
 85.00000;-49.25000;-7.04000;,
 -85.00000;-49.25330;-7.03850;,
 -85.00000;-40.00000;-5.58000;,
 85.00000;-40.00000;-5.47000;,
 91.41000;-40.00000;-7.04000;,
 91.41370;-49.25160;-7.03890;,
 85.00000;-49.25000;-7.04000;,
 -91.41370;-49.25160;-7.03890;,
 -91.41000;-40.00000;-7.04000;,
 91.41000;-40.00000;-7.04000;,
 91.41370;-40.00000;1.42890;,
 91.41370;-49.25160;-7.03890;,
 -91.41000;-40.00000;-7.04000;,
 -91.41370;-49.25160;-7.03890;,
 -91.41370;-40.00000;1.42890;,
 91.41370;-40.00000;1.42890;,
 85.00000;-39.99840;1.42930;,
 85.00000;-49.25000;1.42890;,
 91.41370;-49.25160;1.42850;,
 -91.41370;-40.00000;1.42890;,
 -91.41370;-49.25160;1.42850;,
 -85.00000;-49.25330;1.42890;,
 -85.00000;-40.00160;1.42930;,
 0.00000;-40.00000;1.42890;,
 85.00000;49.25160;-7.03920;,
 85.00000;-49.25000;-7.04000;,
 91.41000;-40.00000;-7.04000;,
 -91.41000;-40.00000;-7.04000;;
 
 47;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;28,31,32,33;,
 4;34,35,36,37;,
 4;34,37,38,39;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;48,51,52,53;,
 4;45,54,55,56;,
 4;45,56,57,46;,
 4;58,59,26,60;,
 4;58,60,61,62;,
 4;63,64,65,66;,
 4;63,66,30,67;,
 4;68,69,70,71;,
 4;68,71,72,73;,
 4;74,75,76,77;,
 4;74,77,78,79;,
 4;71,70,32,80;,
 4;71,80,81,72;,
 4;77,76,81,80;,
 4;77,80,32,78;,
 4;82,83,84,85;,
 4;86,87,88,89;,
 4;85,84,90,91;,
 4;92,93,22,94;,
 4;95,96,38,97;,
 4;98,73,72,99;,
 4;98,99,100,101;,
 4;102,103,104,105;,
 4;102,105,76,75;,
 4;99,72,81,106;,
 4;99,106,36,100;,
 4;105,104,36,106;,
 4;105,106,81,76;,
 3;107,32,25;,
 3;108,23,36;,
 3;109,61,93;,
 3;110,97,65;;
 
 MeshMaterialList {
  3;
  47;
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.228800;0.228800;0.228800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\attack_Reflection_board.jpg";
   }
  }
 }
 MeshNormals {
  71;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000249;1.000000;0.000000;,
  -0.000265;-1.000000;0.000000;,
  0.000133;1.000000;-0.000100;,
  -0.000249;-1.000000;0.000000;,
  0.000033;1.000000;-0.000116;,
  -0.000070;-1.000000;0.000002;,
  -0.000017;1.000000;-0.000124;,
  0.000019;-1.000000;0.000003;,
  -0.000115;-1.000000;0.000000;,
  0.000056;1.000000;-0.000151;,
  0.000118;1.000000;-0.000024;,
  -0.000123;-1.000000;0.000003;,
  -0.087533;0.060997;-0.994292;,
  0.083857;0.059743;-0.994685;,
  -0.174601;0.040838;-0.983792;,
  0.166687;0.038386;-0.985262;,
  1.000000;-0.000012;-0.000273;,
  -1.000000;-0.000012;-0.000273;,
  0.000029;0.000000;1.000000;,
  -0.000029;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  -0.085584;-0.058832;-0.994592;,
  0.083692;-0.058622;-0.994766;,
  -0.170631;-0.038789;-0.984571;,
  0.166542;-0.038396;-0.985286;,
  1.000000;-0.000012;-0.000055;,
  -1.000000;-0.000012;-0.000055;,
  0.000029;0.000017;1.000000;,
  -0.000029;0.000017;1.000000;,
  -0.000000;0.000017;1.000000;,
  1.000000;0.000100;-0.000327;,
  -1.000000;0.000100;-0.000327;,
  0.000029;-0.000017;1.000000;,
  -0.000029;-0.000017;1.000000;,
  0.000000;-0.000017;1.000000;,
  0.055381;-0.116423;-0.991654;,
  -0.055409;-0.116476;-0.991647;,
  -0.110566;-0.076725;-0.990903;,
  0.110502;-0.076619;-0.990918;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000059;-0.000254;,
  -1.000000;0.000059;-0.000254;,
  -1.000000;0.000000;0.000000;,
  0.000062;0.000017;1.000000;,
  0.000062;0.000043;1.000000;,
  0.000029;0.000043;1.000000;,
  0.000062;0.000000;1.000000;,
  -0.000062;0.000017;1.000000;,
  -0.000062;0.000000;1.000000;,
  -0.000029;0.000043;1.000000;,
  -0.000062;0.000043;1.000000;,
  -0.000000;0.000043;1.000000;,
  -0.059256;0.122138;-0.990743;,
  0.055689;0.119344;-0.991290;,
  -0.118521;0.082132;-0.989549;,
  0.110793;0.076589;-0.990888;,
  1.000000;0.000200;-0.000218;,
  -1.000000;0.000200;-0.000218;,
  0.000062;-0.000017;1.000000;,
  0.000029;-0.000043;1.000000;,
  0.000062;-0.000043;1.000000;,
  -0.000062;-0.000017;1.000000;,
  -0.000062;-0.000043;1.000000;,
  -0.000029;-0.000043;1.000000;,
  0.000000;-0.000043;1.000000;;
  47;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;11,9,9,14;,
  4;10,15,8,8;,
  4;16,6,6,16;,
  4;16,16,12,10;,
  4;17,11,13,17;,
  4;17,17,7,7;,
  4;27,18,19,28;,
  4;27,28,41,42;,
  4;27,42,43,29;,
  4;27,29,20,18;,
  4;28,19,21,30;,
  4;28,30,44,41;,
  4;31,45,45,31;,
  4;31,31,22,46;,
  4;32,47,23,32;,
  4;32,32,48,48;,
  4;49,50,51,33;,
  4;49,33,24,52;,
  4;53,54,25,34;,
  4;53,34,55,56;,
  4;33,51,57,35;,
  4;33,35,26,24;,
  4;34,25,26,35;,
  4;34,35,57,55;,
  4;18,58,59,19;,
  4;18,20,60,58;,
  4;19,59,61,21;,
  4;46,36,62,62;,
  4;47,63,63,37;,
  4;64,52,24,38;,
  4;64,38,65,66;,
  4;67,68,69,39;,
  4;67,39,25,54;,
  4;38,24,26,40;,
  4;38,40,70,65;,
  4;39,69,70,40;,
  4;39,40,26,25;,
  3;10,12,15;,
  3;11,14,13;,
  3;46,22,36;,
  3;47,37,23;;
 }
 MeshTextureCoords {
  111;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.750000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.750000;1.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.250000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.929258;0.157264;,
  0.929258;0.842736;,
  0.070742;0.842736;,
  0.070742;0.157278;,
  0.500000;0.250000;,
  0.250000;0.250000;,
  0.250000;0.000000;,
  0.500000;0.000000;,
  0.750000;0.250000;,
  0.750000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  1.000000;0.500000;,
  0.750000;0.500000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.000000;0.250000;,
  0.000000;0.000000;,
  0.000000;0.250000;,
  0.000000;0.000000;,
  1.000000;0.250000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.250000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  0.000000;0.250000;,
  1.000000;0.000000;,
  0.000000;0.250000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.250000;,
  1.000000;0.500000;,
  0.750000;0.500000;,
  0.750000;0.250000;,
  0.750000;0.000000;,
  1.000000;0.000000;,
  0.500000;0.250000;,
  0.500000;0.500000;,
  0.500000;0.750000;,
  0.500000;1.000000;,
  0.250000;1.000000;,
  0.250000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  1.000000;1.000000;,
  0.750000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.750000;,
  0.000000;1.000000;,
  1.000000;0.750000;,
  1.000000;1.000000;,
  0.000000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.750000;,
  1.000000;1.000000;,
  0.750000;1.000000;,
  0.750000;0.750000;,
  0.500000;0.750000;,
  0.625000;1.000000;,
  0.625000;0.000000;,
  0.000000;0.625000;,
  1.000000;0.625000;;
 }
}