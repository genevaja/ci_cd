#!/bin/bash

TEXT="Deploy status:+$1%0A%0AProject:+$CI_PROJECT_NAME%0AURL:+$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/%0ABranch:+$CI_COMMIT_REF_SLUG"

curl -s "https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage?text=$TEXT&chat_id=$USER_ID" > /dev/null
