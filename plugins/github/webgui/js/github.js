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

    //model.addService('githubservice', 'GitHubService', GitHubServiceClient);

    var ProjectHostingServiceNavigator = declare(HtmlTree, {
        constructor : function () {
            var that = this;

            this._data = [];

            this._store = new Observable(new Memory({
                data : this._data,
                getChildren : function (node) {
                    return node.getChildren ? node.getChildren(node) : [];
                }
            }));

            var dataModel = new ObjectStoreModel({
                store : that._store,
                query : { id : 'root' },
                mayHaveChildren : function (node) {
                    return node.hasChildren;
                }
            });

            //--- Tree ---//
            // ezt a gitNavigator.js-ből vettem, nem kell így hagyni
            this._data.push({
                id          : 'root',
                name        : 'List of repositories',
                cssClass    : 'icon-list',
                hasChildren : true,
                getChildren : function () {
                    return that._store.query({ parent : 'root' });
                }
            });

            this.set('model', dataModel);
            this.set('openOnClick', false);
        }
    });

    var navigator = new ProjectHostingServiceNavigator({
        id    : 'hostnavigator',
        title : 'Project Hosting Service Navigator'
    });

    viewHandler.registerModule(navigator, {
        type : viewHandler.moduleType.Accordion,
        priority : 50
    });

});