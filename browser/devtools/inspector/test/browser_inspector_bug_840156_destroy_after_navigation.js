/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

let temp = {};
Cu.import("resource://gre/modules/commonjs/sdk/core/promise.js", temp);
let Promise = temp.Promise;
temp = {};
Cu.import("resource:///modules/devtools/Toolbox.jsm", temp);
let Toolbox = temp.Toolbox;
temp = {};
Cu.import("resource:///modules/devtools/Target.jsm", temp);
let TargetFactory = temp.TargetFactory;
temp = null;

function test() {
  waitForExplicitFinish();

  const URL_1 = "data:text/plain;charset=UTF-8,abcde";
  const URL_2 = "data:text/plain;charset=UTF-8,12345";

  let target, toolbox;

  // open tab, load URL_1, and wait for load to finish
  let tab = gBrowser.selectedTab = gBrowser.addTab();
  let target = TargetFactory.forTab(gBrowser.selectedTab);
  let deferred = Promise.defer();
  let browser = gBrowser.getBrowserForTab(tab);
  function onTabLoad() {
    browser.removeEventListener("load", onTabLoad, true);
    deferred.resolve(null);
  }
  browser.addEventListener("load", onTabLoad, true);
  browser.loadURI(URL_1);

  // open devtools panel
  deferred.promise
    .then(function () gDevTools.showToolbox(target, null, Toolbox.HostType.BOTTOM))
    .then(function (aToolbox) { toolbox = aToolbox; })

  // select the inspector
    .then(function () toolbox.selectTool("inspector"))

  // navigate to URL_2
    .then(function () {
      let deferred = Promise.defer();
      target.once("navigate", function () deferred.resolve());
      browser.loadURI(URL_2);
      return deferred.promise;
    })

  // destroy the toolbox (and hence the inspector) before the load completes
    .then(function () toolbox.destroy())

  // this (or any other) exception should not occur:
  // [JavaScript Error: "TypeError: self.selection is null" {file: "resource:///modules/devtools/InspectorPanel.jsm" line: 250}]

    .then(function cleanUp() {
      gBrowser.removeCurrentTab();
      finish();
    });
}
