#pragma once

#define CONCAT_CONST_CHAR_2(a, b) a"" b
#define CONCAT_CONST_CHAR_3(a, b, c) CONCAT_CONST_CHAR_2(a, b)"" c
#define CONCAT_CONST_CHAR_4(a, b, c, d) CONCAT_CONST_CHAR_3(a, b, c)"" d

//#define MY_NAME "shima"
//
//#define TEST_SKIN_NAME "SK_Mannequin_asset_reference_node_inputs_editor"
//#define ASSET_REFERENCE_GRAPH_FILE_NAME "AssetReferenceGraph.bin"
//#define ASSET_REFERENCE_TEST_CURRENT_WORKING_DIR_PATH CONCAT_CONST_CHAR_3("charactor/player/", TEST_SKIN_NAME, "/")
//
//	int main()
//	{
//		printf("%s\n", CONCAT_CONST_CHAR_2(MY_NAME, "haike"));
//		printf("%s\n", CONCAT_CONST_CHAR_3(MY_NAME, "haike", "bucuo"));
//		printf("%s\n", CONCAT_CONST_CHAR_4(MY_NAME, "haike", "bucuo", "nihao"));
//
//		printf("%s\n", CONCAT_CONST_CHAR_2(ASSET_REFERENCE_TEST_CURRENT_WORKING_DIR_PATH, ASSET_REFERENCE_GRAPH_FILE_NAME));
//
//		return 0;
//	}
