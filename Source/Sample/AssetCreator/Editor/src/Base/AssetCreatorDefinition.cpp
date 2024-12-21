#include "AssetCreatorDefinition.h"
#include "Niflect/Util/SystemUtil.h"

namespace AssetCreatorDefinition
{
    namespace DirPath
    {
        Niflect::CString GetExampleAssetDirPath()
        {
#define ASSET_CREATOR_DIR_PATH_EXAMPLE_ASSET "../../../../../../../Source/Sample/AssetCreator/ExampleAsset"
            return NiflectUtil::ResolvePath(ASSET_CREATOR_DIR_PATH_EXAMPLE_ASSET);
        }
    }
}
