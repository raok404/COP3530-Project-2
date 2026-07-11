import QtQuick
import QtQuick.Dialogs // file picking dialog window
import QtQuick.Layouts // arrange items in UI
import QtQuick.Controls // for things like buttons and dropdown list
import QtQuick.Controls.Material // for the beauty of the application

Window {
    id: root
    width: 960
    height: 640
    visible: true
    title: qsTr("Logs filter")

    property bool usePageView: (width  / height) < 1.0
    readonly property string view1: "Ingredients"
    readonly property string view2: "Recipe"
    readonly property string view3: "CookBook"

    // component for the ingredient list part
    Component {
        id: viewOne
        // Rectangle { // place holder
        //     color: "lightblue"
        //     Text { text: qsTr(view1); anchors.centerIn: parent }
        // }
        ColumnLayout {
            spacing: 12
            anchors.fill: parent
            anchors.margins: 6
            anchors.rightMargin: 3
            GroupBox {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop
                ColumnLayout {
                    spacing: 6
                    anchors.fill: parent
                    RowLayout {
                        Label {
                            text: "Type: "
                            font.pixelSize: 14
                        }
                        ComboBox {
                            id: ingredientType
                            model: ["None", "Vegetable", "Meat", "Seafood", "Fruit", "Condiment", "Spice"]
                            currentIndex: 0
                            Layout.fillWidth: true
                            implicitHeight: 36

                            onActivated: {
                                console.log("Selected Text: ", ingredientType.currentText)
                            }
                        }
                    }
                    RowLayout {
                        TextField {
                            id: ingredientSearch
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            placeholderText: qsTr("Search...")
                            font.pointSize: 8
                            implicitHeight: 30

                            onTextChanged: {
                                console.log("Text Changed Data :", ingredientSearch.text)
                            }
                        }
                    }
                }
            }
            // lists of ingredients shown below
            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                ListView {
                    id: ingredientsView
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    model: ingredientModel
                    delegate: itemsListViewDelegate
                    property string viewType: "ingredients"
                    // highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
                    focus: true
                    clip: true
                    ScrollBar.vertical: ScrollBar {
                        topPadding: 2
                        id: ingredientScrollBar
                        width: 16
                        policy: ScrollBar.AlwaysOn
                        active: ScrollBar.AlwaysOn
                    }
                    onAtYEndChanged: {
                        if (atYEnd) {
                            // Trigger your bottom-reached action here
                            console.log("Reached the bottom of the list!");
                            // loadMoreData();
                        }
                    }
                }
            }
        }
    }

    // component for the recipe pages
    Component {
        id: viewTwo
        ColumnLayout {
            spacing: 0
            anchors.fill: parent
            anchors.margins: 6
            anchors.rightMargin: 3
            anchors.leftMargin: 3
            TabBar {
                id: kitchenBookmark
                Layout.fillWidth: true
                currentIndex: kitchenBookmarkPages.currentIndex
                width: parent.width
                clip: true

                onCurrentIndexChanged: kitchenBookmarkPages.currentIndex = currentIndex

                TabButton { text: qsTr("Home"); width: 84 }
                Repeater {
                    model: bookmark
                    TabButton {
                        //anchors.fill: parent
                        width: implicitWidth + 84
                        Label {
                            id: tabLabel
                            text: model.title
                            anchors.centerIn: parent
                        }
                        AbstractButton {
                            id: closingbutton
                            height: 16
                            width: 16
                            padding: 0

                            anchors.right: parent.right
                            anchors.rightMargin: 5
                            anchors.verticalCenter: parent.verticalCenter

                            hoverEnabled: true

                            background: Rectangle {
                                color: parent.hovered ? "#999999" : "transparent"
                                radius: width / 2
                            }
                            contentItem: Text {
                                text: parent.text
                                font: parent.font
                                color: parent.hovered ? "black" : "#999999"
                                anchors.fill: parent
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter - 20
                            }
                            text: "×"
                            font.pixelSize: 11
                            font.bold: true

                            onClicked: {
                                var bar = kitchenBookmark;
                                var deletedIndex = index + 1;
                                var oldCurrentIndex = kitchenBookmark.currentIndex;

                                bookmark.remove(index);

                                Qt.callLater(() => {
                                    if (deletedIndex < oldCurrentIndex) {
                                        bar.currentIndex = oldCurrentIndex - 1;
                                    }
                                    else if (deletedIndex === oldCurrentIndex) {
                                        bar.currentIndex = Math.max(0, oldCurrentIndex - 1);
                                    }
                                    else {
                                        bar.currentIndex = oldCurrentIndex;
                                    }
                                });
                            }
                        }
                    }
                }
            }
            StackLayout {
                id: kitchenBookmarkPages
                Layout.fillWidth: true
                Layout.fillHeight: true
                currentIndex: 0

                Item {
                    Loader { anchors.fill: parent; sourceComponent: home}
                }

                Repeater {
                    model: bookmark

                    // This is the template for our pages
                    Rectangle {
                        color: model.pageColor

                        ColumnLayout {
                            anchors.fill: parent
                            anchors.leftMargin: 6
                            anchors.rightMargin: 6
                            spacing: 2

                            Text {
                                text: model.title
                                font.bold: true
                                font.underline: true
                                font.pointSize: 24
                                lineHeight: 1.5
                                lineHeightMode: Text.ProportionalHeight
                                wrapMode: Text.Wrap
                                //layout.horizontalCenter: parent
                            }

                            Text {
                                text: "Ingredients: "
                                font.bold: true
                                font.pixelSize: 18
                                lineHeight: 1.5
                                lineHeightMode: Text.ProportionalHeight
                                wrapMode: Text.Wrap
                            }

                            Text {
                                leftPadding: 10
                                text: model.ingredients
                                font.pixelSize: 14
                                lineHeight: 1.5
                                lineHeightMode: Text.ProportionalHeight
                                wrapMode: Text.Wrap
                            }
                            Text {
                                text: "Instructions: "
                                font.bold: true
                                font.pixelSize: 18
                                lineHeight: 1.5
                                lineHeightMode: Text.ProportionalHeight
                                wrapMode: Text.Wrap
                            }
                            Text {
                                Layout.fillWidth: true
                                text: model.instructions
                                //anchors.horizontalCenter: parent
                                font.pixelSize: 16
                                lineHeight: 1.5
                                lineHeightMode: Text.ProportionalHeight
                                wrapMode: Text.Wrap
                            }
                            Item {
                                Layout.fillHeight: true
                            }
                        }
                    }
                }

            }
        }
    }

    // component for the cookbook page
    Component {
        id: viewThree
        ColumnLayout {
            spacing: 12
            anchors.fill: parent
            anchors.margins: 6
            anchors.leftMargin: 3
            GroupBox {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop
                ColumnLayout {
                    spacing: 6
                    anchors.fill: parent
                    Layout.fillWidth: true
                    RowLayout {
                        Label {
                            text: "Type: "
                            font.pixelSize: 14
                        }
                        ComboBox {
                            id: recipeType
                            model: ["None", "Breakfast", "Lunch", "Dinner", "Dessert", "Drink"]
                            currentIndex: 0
                            Layout.fillWidth: true
                            implicitHeight: 36

                            onActivated: {
                                console.log("Selected Text: ", recipeType.currentText)
                            }
                        }
                    }
                    ColumnLayout {
                        Layout.alignment: Qt.AlignLeft
                        Layout.fillWidth: true
                        spacing: 0

                        Button {
                            id: dropdownHeader
                            Layout.fillWidth: true
                            Layout.alignment: Qt.AlignLeft
                            implicitHeight: 30


                            contentItem: Text {
                                text: dropdownHeader.text
                                font: dropdownHeader.font
                                color: dropdownHeader.down ? "#0055FF" : "#333333"
                                width: dropdownHeader.width

                                horizontalAlignment: Text.AlignLeft
                                verticalAlignment: Text.AlignVCenter
                            }

                            text: (checkboxContainer.visible ? "\u23F7" : "\u23F5") + qsTr(" Recipe content")
                            font.pixelSize: 12
                            font.bold: true
                            leftPadding: 0




                            onClicked: checkboxContainer.visible = !checkboxContainer.visible

                            background: Rectangle {
                                //color: "#f6f6f6"
                                //border.color: "#bdbebf"
                                //radius: 4
                            }
                        }
                        ColumnLayout {
                            id: checkboxContainer
                            visible: false
                            spacing: 4
                            Layout.bottomMargin: 6

                            ColumnLayout {
                                spacing: 2
                                Layout.leftMargin: 6
                                CheckBox {
                                    id: includeCarb
                                    implicitHeight: 18
                                    font.pixelSize: 8
                                    text: qsTr("Carb")
                                }

                                CheckBox {
                                    id: includeProtein
                                    implicitHeight: 18
                                    font.pixelSize: 8
                                    text: qsTr("Protein")
                                }

                                CheckBox {
                                    id: includeFiber
                                    implicitHeight: 18
                                    font.pixelSize: 8
                                    text: qsTr("Fiber")
                                }

                                CheckBox {
                                    id: includeFruit
                                    implicitHeight: 18
                                    font.pixelSize: 8
                                    text: qsTr("Fruiit")
                                }

                                CheckBox {
                                    id: includeDairy
                                    implicitHeight: 18
                                    font.pixelSize: 8
                                    text: qsTr("Dairy")
                                }
                            }
                        }
                    }
                    RowLayout {
                        TextField {
                            id: recipeSearch
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            placeholderText: qsTr("Search...")
                            font.pointSize: 8
                            implicitHeight: 30

                            onTextChanged: {
                                console.log("Text Changed Data :", recipeSearch.text)
                            }
                        }
                    }
                }
            }
            // lists of ingredients shown below
            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                ListView {
                    id: recipeView
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    model: recipeModel
                    delegate: itemsListViewDelegate
                    property string viewType: "recipes"
                    // highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
                    focus: true
                    clip: true
                    ScrollBar.vertical: ScrollBar {
                        topPadding: 2
                        id: recipeScrollBar
                        width: 16
                        policy: ScrollBar.AlwaysOn
                        active: ScrollBar.AlwaysOn
                    }
                    onAtYEndChanged: {
                        if (atYEnd) {
                            // Trigger your bottom-reached action here
                            console.log("Reached the bottom of the list!");
                            // loadMoreData();
                        }
                    }
                }
            }
        }
    }

    ListModel {
        id: recipeModel
        ListElement {
            name: "Chicken sandwich"
        }
        ListElement {
            name: "Noodle"
        }
        ListElement {
            name: "Spaghetti"
        }
        ListElement {
            name: "fried rice"
        }
        ListElement {
            name: "dumplings"
        }
        ListElement {
            name: "salad"
        }
        ListElement {
            name: "steak"
        }
        ListElement {
            name: "salmon steak"
        }
        ListElement {
            name: "ice cream"
        }
        ListElement {
            name: "baked potatoes"
        }
        ListElement {
            name: "bread"
        }
        ListElement {
            name: "pho"
        }
        ListElement {
            name: "omelette"
        }
        ListElement {
            name: "canned tuna"
        }
        ListElement {
            name: "placeholder"
        }

    }

    ListModel {
        id: ingredientModel
        ListElement {
            name: "cabbage"
        }
        ListElement {
            name: "rice"
        }
        ListElement {
            name: "flour"
        }

    }

    ListModel {
        id: bookmark
    }

    Component {
        id: itemsListViewDelegate
        Item {
            id: myItem
            required property string name
            height: 40
            width: ListView.view.width - 16

            Button {
                anchors.fill: parent
                leftPadding: 0
                rightPadding: 10
                contentItem: Text {
                    text: parent.text
                    font: parent.font
                    color: parent.down ? "#555555" : "#333333"
                    width: parent.width
                    height:parent.height
                    leftPadding: 6
                }


                text: myItem.name
                font.pixelSize: 16
                font.bold: true

                background: Rectangle {
                    height: parent.height
                    width: parent.width
                    anchors.fill: parent
                    color: "Black"
                    opacity: parent.down ? 0.25 : 0
                }

                onClicked: {
                    if (myItem.ListView.view.viewType === "recipes") {
                        bookmark.append({
                            "title" : myItem.name,
                            "pageColor" : "#f0f0f0",
                            "ingredients" : "- skinless boneless chicken halves\n- butter\n- condensed cream chicken soup\n- onion\n- biscuit dough torn",
                            "instructions": "Place the chicken, butter, soup, and onion in a slow cooker, and fill with enough water to cover.\nCover, and cook for 5 to 6 hours on High. About 30 minutes before serving, place the torn biscuit dough in the slow cooker. Cook until the dough is no longer raw in the center.\n"
                        });
                    } else if (myItem.ListView.view.viewType === "ingredients") {
                        // nothing happens for now since our data doesn't have contents for the ingredients
                        // bookmark.append({
                        //     "title" : myItem.name,
                        //     "pageColor" : "#f0f0f0",
                        //     "ingredients" : "- skinless boneless chicken halves\n- butter\n- condensed cream chicken soup\n- onion\n- biscuit dough torn",
                        //     "instructions": "Place the chicken, butter, soup, and onion in a slow cooker, and fill with enough water to cover.\nCover, and cook for 5 to 6 hours on High. About 30 minutes before serving, place the torn biscuit dough in the slow cooker. Cook until the dough is no longer raw in the center.\n"
                        // });
                    }

                }
            }
        }
    }

    Component {
        id: home
        ColumnLayout {
            anchors.fill: parent
            spacing: 17
            Rectangle {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Text {
                    anchors.fill: parent
                    anchors.margins: 6
                    text: {"\tWelcome to Ratatouille!\n recipe on the right will be displayed if the ingredient on the left is available :D.\n" +
                           "Click on the recipe or ingredient to find out informations about them.\n" +
                           "if you want to register an ingredient or a recipe then enter the box below and click the button."
                    }
                    font.pixelSize: 14
                    lineHeight: 1.5
                    lineHeightMode: Text.ProportionalHeight
                    wrapMode: Text.Wrap
                }
            }



            GroupBox {
                Layout.fillWidth: true
                ColumnLayout {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    Text {
                        text: "Register New Ingredient"
                    }
                    RowLayout {

                        Layout.fillWidth: true
                        Text {
                            text: "ingredient name"
                            font.bold: true
                        }
                        TextField {
                            id: ingredientRegister
                            Layout.fillWidth: true
                            placeholderText: qsTr("Name")
                            font.pointSize: 8
                            implicitHeight: 30
                        }
                        Button {
                            id: ingredientRegisterButton
                            text: "Register"
                            font.bold: true
                            contentItem: Text {
                                text: ingredientRegisterButton.text
                                font: ingredientRegisterButton.font
                                color: ingredientRegisterButton.down ? "#bababa" : "#383838"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }
                            background: Rectangle {
                                color: ingredientRegisterButton.down ? "#383838" : "#aaaaaa"
                                radius: 4
                            }
                            onClicked: {
                                ingredientRegister.clear()
                            }
                        }
                    }
                }
            }
            GroupBox {
                Layout.fillWidth: true
                ColumnLayout {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    spacing: 10
                    Text {
                        text: "Register New Recipe"

                    }

                    RowLayout {
                        Layout.fillWidth: true
                        Text {
                            text: "Recipe Name"
                            font.bold: true
                        }
                        TextField {
                            id: recipeNameRegister
                            Layout.fillWidth: true
                            placeholderText: qsTr("Name")
                            font.pointSize: 8
                            implicitHeight: 42

                        }

                    }
                    RowLayout {
                        Layout.fillWidth: true
                        Text {
                            text: "Recipe Ingredients"
                            font.bold: true
                        }
                        TextField {
                            id: recipeIngredientRegister
                            Layout.fillWidth: true
                            placeholderText: qsTr("Ingredients")
                            font.pointSize: 8
                            implicitHeight: 42
                        }
                    }
                    RowLayout {
                        Layout.fillWidth: true
                        Text {
                            text: "Recipe Steps"
                            font.bold: true
                        }
                        TextField {
                            id: recipeStepsRegister
                            Layout.fillWidth: true
                            placeholderText: qsTr("Steps")
                            font.pointSize: 8
                            implicitHeight: 42
                        }
                    }
                    Button {
                        id: recipeRegisterButton
                        text: "Register"
                        font.bold: true
                        contentItem: Text {
                            text: recipeRegisterButton.text
                            font: recipeRegisterButton.font
                            color: recipeRegisterButton.down ? "#bababa" : "#383838"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                        background: Rectangle {
                            color: recipeRegisterButton.down ? "#383838" : "#aaaaaa"
                            radius: 4
                        }
                        Layout.alignment: Qt.AlignHCenter
                        onClicked: {
                            recipeNameRegister.clear()
                            recipeIngredientRegister.clear()
                            recipeStepsRegister.clear()
                        }
                    }
                }
            }

        }
    }

    // statement on which component below to show depending on the window size ratio
    Loader {
        anchors.fill: parent
        sourceComponent: root.usePageView ? pageViewComponent : splitViewComponent
    }

    // component for when the window is taller than wider for maybe mobile support?
    Component {
        id: pageViewComponent
        ColumnLayout {
            anchors.fill: parent
            TabBar {
                id: tabBar
                Layout.fillWidth: true
                currentIndex: stackLayout.currentIndex

                onCurrentIndexChanged: stackLayout.currentIndex = currentIndex

                TabButton { text: qsTr(view1) }
                TabButton { text: qsTr(view2) }
                TabButton { text: qsTr(view3) }
            }

            StackLayout {
                id: stackLayout
                Layout.fillWidth: true
                Layout.fillHeight: true
                currentIndex: 1

                Item {
                    Loader { anchors.fill: parent; sourceComponent: viewOne}
                }

                Item {
                    Loader { anchors.fill: parent; sourceComponent: viewTwo}
                }

                Item {
                    Loader { anchors.fill: parent; sourceComponent: viewThree}
                }

            }
        }
    }

    // component for when the window is wider than taller
    Component {
        id: splitViewComponent
        SplitView {
            id: splitView
            anchors.fill: parent
            orientation: Qt.Horizontal

            handle: Rectangle {
                id: handleDelegate
                implicitWidth: 4
                implicitHeight: 4
                color: SplitHandle.pressed ? "#aaaaaa"
                    : (SplitHandle.hovered ? Qt.darker("#f0f0f0", 1.1) : "#f0f0f0")

                containmentMask: Item {
                    x: (handleDelegate.width - width) / 2
                    width: 32
                    height: splitView.height
                }
            }

            Item {
                SplitView.preferredWidth: 212
                SplitView.fillHeight: true
                Loader { anchors.fill: parent; sourceComponent: viewOne}
            }

            Item {
                SplitView.fillWidth: true
                SplitView.fillHeight: true
                Loader { anchors.fill: parent; sourceComponent: viewTwo}
            }

            Item {
                SplitView.preferredWidth: 212
                SplitView.fillHeight: true
                Loader { anchors.fill: parent; sourceComponent: viewThree}
            }
        }
    }
}