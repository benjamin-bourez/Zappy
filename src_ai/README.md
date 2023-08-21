# [ INCANTATION PROTOCOL ]

<h2> Here is explained the way our AI interact which each other by broadcasting. </h2>

<h3> How it works ? </h3>
<p> An AI send to the server a broadcast in the format : "Broadcast message\n",</br>
then the server will send to the client the following message : "message K, text\n",</br>
where K is the direction the message come from.<p>

<h3> Protocol. </h3>

<p> "Broadcast [COMMAND_NAME] {OPTIONAL_INFORMATION}\n" -> Used when a player need another to perform a command.</p>
<p> "Broadcast ID [ID]\n" -> Send is ID to the others AI.</p>
<p> "Broadcast INCANTATE [ID] WANT [LEVEL]\n" -> Used when a player want to start an incantation.</p>
<p> "Broadcast INCANTATE [ID_INCANTER] [ID]\n" -> Response of an AI for the incantation (positive).</p>
<p> "Broadcast INCANTATE [ID_INCANTER] WAIT [ID] [ID] ...\n" -> AI waiting for other AI to come, with the list of AI needed.</p>
<p> "Broadcast STOP_FORK\n" -> Used when an AI know there is 8 AI or more and want everyone to stop forks.</p>

<h3> AI message received : </h3>

<p> "message [DIRECTION], [BROADCAST_MESSAGE] </p>
_bufferOfCommands.push_back(_broadcast->SendBroadcast("INCANTATE " + _id + " WANT" + std::to_string(_level) + "\n"));