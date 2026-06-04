import { connectedWebSocket, sendInsert } from './websocket.js';
import { renderTree } from './renderer.js';

let currentTreeType = "btree";


const inputBox = document.getElementById("inputBox");
const submitButton = document.getElementById("submitBtn");
const switchButton = document.getElementById("switchBtn");
const statusText = document.getElementById("status");

initialize();

function initialize() {
    statusText.textContent = "Connecting to backend..."";

    connectWebSocket({
        onOpen: handleConnectionOpen,
        onMessage: handleServerMessage,
        onClose: handleConnectionClosed
    });

    setupEventListeners();
}

function setupEventListeners() {
    submitButton.addEventListener("click", handleInsert);
    switchButton.addEventListener("click", switchTreeType);
}

function handleInsert() {
    const value = parseInt(inputBox.value);

    if (isNaN(value)) {
        alert("Please enter a valid number");
        return;
    }

    sendInsert({
        treeType: currentTreeType,
        value:value
    });

    inputBox.value = "";
}

function switchTreeType() {
    if (currentTreeType === "btree") {
        currentTreeType = "redblack";
    } else {
        currentTreeType = "btree";
    }

    switchButton.textContent = `Switch to ${currentTreeType}`;
}

function handleConnectionOpen() {
    statusText.textContent = "Connected";
}

function handleServerMessage(message) {
    if (message.type === "tree_update") {
        renderTree(message.tree);
    }
}

function handleConnectionClosed() {
    statusText.textContent = "Disconnected";
}
