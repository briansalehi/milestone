#!/usr/bin/env python3

from http.server import BaseHTTPRequestHandler, HTTPServer
import json

class Handler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == "/subjects":
            data = {"subjects": [{"id": 1, "name": "Mathematics"}, {"id": 2, "name": "Physics"}]}
        elif self.path == "/resources":
            data = {"resources": [{"id": 1, "name": "Thomas' Calculus"}, {"id": 2, "name": "Fundamentals of Physics"}]}
        else:
            self.send_error(404, "Not found")
            return

        body = json.dumps(data).encode()

        self.send_response(200)
        self.send_header("Content-Type", "application/json")
        self.send_header("Content-Length", str(len(body)))
        self.end_headers()
        self.wfile.write(body)

    def log_message(self, *args, **kwargs):
        pass

if __name__ == "__main__":
    server = HTTPServer(("127.0.0.1", 9821), Handler)
    print("Listening")
    server.serve_forever()
