<?php
function sendResponse() {

    $response  = '<?xml version="1.0" encoding="utf-8"?>';
    if($_POST["email"] === "test@juce.com" and $_POST["pw"] === "test")
        $response .= '<MESSAGE message="Thanks for registering our product!"><KEY>INSERT_KEY_HERE</KEY></MESSAGE>';
    else
        $response .= '<ERROR error="Sorry, we were not able to authorise your request. Please provide a valid email address and password."></ERROR>';

    return $response;
}

header("Content-type: text/xml; charset=utf-8");
echo sendResponse();
?>
