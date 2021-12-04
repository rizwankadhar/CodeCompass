require([
    'dijit/Tooltip',
    'dijit/tree/ObjectStoreModel',
    'dojo/_base/declare',
    'dojo/store/Memory',
    'dojo/store/Observable',
    'dojo/topic',
    'codecompass/view/component/HtmlTree',
    'codecompass/model',
    'codecompass/viewHandler'],
function (Tooltip, ObjectStoreModel, declare, Memory, Observable, topic,
    HtmlTree, model, viewHandler) {

    var ProjectHostingServiceNavigator = declare(HtmlTree, {
        constructor : function () {
            var that = this;
            this._data = [];
        }
    });

    var navigator = new ProjectHostingServiceNavigator({
        id    : 'hostnavigator',
        title : 'Project Hosting Service Navigator'
    });

    viewHandler.registerModule(navigator, {
        type : viewHandler.moduleType.Accordion
    });


});