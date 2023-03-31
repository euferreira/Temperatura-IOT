#!/bin/bash

if ( ! -f ".env" ); then
  cp .env.example .env
fi

sleep 2

npm install
npm run start:dev
