require([
  'dojo/_base/declare',
  'dojo/dom-construct',
  'dojo/topic',
  'dojo/dom-style',
  'dijit/MenuItem',
  'dijit/form/Button',
  'dijit/form/CheckBox',
  'dijit/form/Select',
  'dijit/layout/ContentPane',
  'codecompass/viewHandler',
  'codecompass/urlHandler',
  'codecompass/model'],
function (declare, dom, topic, style, MenuItem, Button, CheckBox, Select,
  ContentPane, viewHandler, urlHandler, model) {
  
  model.addService('yamlservice', 'YamlService', YamlServiceClient);

  var fileDiagramHandler = {
    id : 'yaml-file-diagram-handler',

    getDiagram : function (diagramType, fileId, callback) {
      model.yamlservice.getYamlFileDiagram(fileId, callback);
    },

    mouseOverInfo : function (diagramType, fileId) {
      return {
        fileId : fileId,
        selection : [1,1,1,1]
      };
    }
  };

  viewHandler.registerModule(fileDiagramHandler, {
    type : viewHandler.moduleType.Diagram
  });

  var yamlData = {
    id     : 'yamlData',
    render : function (fileInfo) {
      return new MenuItem({
        label    : 'Yaml',
        onClick  : function () {
          topic.publish('codecompass/openDiagram', {
            handler : 'yaml-file-diagram-handler',
            diagramType : 1,
            node : fileInfo.id
          })
        }
      });
    }
  };

  viewHandler.registerModule(yamlData, {
    type : viewHandler.moduleType.FileManagerContextMenu
  });

  var fileInfoHandler = {
    id : 'yaml-file-info-handler',

    getDiagram : function (diagramType, fileId, callback) {
      model.yamlservice.getYamlFileInfo(fileId, callback);
    },

    mouseOverInfo : function (diagramType, fileId) {
      return {
        fileId : fileId,
        selection : [1,1,1,1]
      };
    }
  };

  viewHandler.registerModule(fileInfoHandler, {
    type : viewHandler.moduleType.Diagram
  });

  var YamlInfo = {
    id : 'YamlInfo',
    render : function (fileInfo) {
      return new MenuItem({
        label : 'YamlInfo',
        onClick : function () {
          topic.publish('codecompass/openDiagram', {
            handler : 'yaml-file-info-handler',
            diagramType : 1,
            node : fileInfo.id
          })
        }
      });
    }
  };

  viewHandler.registerModule(YamlInfo, {
    type :  viewHandler.moduleType.FileManagerContextMenu
  });

});