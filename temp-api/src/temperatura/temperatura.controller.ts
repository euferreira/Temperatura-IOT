import { Body, Controller, Get, Param, Post, Query } from "@nestjs/common";
import { TemperaturaService } from "./temperatura.service";
import { Temperatura } from "./temperatura.entity";
import { TemperaturaGateway } from "./temperatura.gateway";

@Controller("temperatura")
export class TemperaturaController {
  constructor(private readonly temperaturaService: TemperaturaService, private readonly temperaturaGateway: TemperaturaGateway) {
  }

  @Get()
  async getTemperatura(): Promise<Temperatura[]> {
    return this.temperaturaService.getTemperatura();
  }

  @Get("last/:limit")
  async getLastsTemperaturas(@Param() params: any): Promise<Temperatura[]> {
    if (params) {
      return this.temperaturaService.getLastsTemperatura(Number(params.limit));
    }
    return this.temperaturaService.getLastsTemperatura(10);
  }

  @Get("last")
  async getLastTemperatura(): Promise<Temperatura> {
    return this.temperaturaService.getLastTemperatura();
  }

  @Post()
  async createTemperatura(@Body() body: Temperatura): Promise<Temperatura> {
    const result = await this.temperaturaService.createTemperatura(body);
    if (this.temperaturaGateway.server) {
      await this.temperaturaGateway.handleGetTemperatura(result);
    }
    return result;
  }
}
