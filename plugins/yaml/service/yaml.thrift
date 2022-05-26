include "project/common.thrift"
include "project/project.thrift"

namespace cpp cc.service.yaml
namespace java cc.service.yaml


service YamlService
{

  string getYamlFileDiagram(
    1:common.FileId fileId)

  string getYamlFileInfo(
    1:common.FileId fileId)

}
