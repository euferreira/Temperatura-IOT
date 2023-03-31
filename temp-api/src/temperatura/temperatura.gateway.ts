import {
  OnGatewayConnection, OnGatewayDisconnect,
  OnGatewayInit,
  SubscribeMessage,
  WebSocketGateway,
  WebSocketServer
} from "@nestjs/websockets";
import { TemperaturaService } from "./temperatura.service";
import { Server } from "socket.io";
import { Logger } from "@nestjs/common";
import { Temperatura } from "./temperatura.entity";

@WebSocketGateway()
export class TemperaturaGateway implements OnGatewayInit, OnGatewayConnection, OnGatewayDisconnect {
  constructor(private readonly temperatureService: TemperaturaService) {
  }

  private logger: Logger = new Logger("TemperaturaGateway");

  @WebSocketServer() server: Server;

  async handleConnection() {
    this.logger.log("Novo usuário conectado");
  }

  async handleDisconnect() {
    this.logger.log("Usuário desconectado");
  }

  async afterInit() {
    try {
      const io = require("socket.io")(this.server, {
        cors: {
          origin: "*"
        }
      });

      io.on("connection", (_) => {
        this.logger.log("Usuário conectado ao socket (=^･ｪ･^=)");
      });
    } catch (error) {
      this.logger.error(`Erro ao inicializar o socket: ${error.message}`);
    }
  }

  @SubscribeMessage("getTemperatura")
  async handleGetTemperatura(temperatura: Temperatura) {
    if (this.server) {
      this.server.emit("getTemperatura", JSON.stringify(temperatura));
    }
  }
}
