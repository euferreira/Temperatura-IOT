import {Body, Controller, Get, Post} from "@nestjs/common";
import {TemperaturaService} from "./temperatura.service";
import {Temperatura} from "./temperatura.entity";

@Controller('temperatura')
export class TemperaturaController {
    constructor(private readonly temperaturaService: TemperaturaService) {}

    @Get()
    async getTemperatura(): Promise<Temperatura[]> {
        return this.temperaturaService.getTemperatura();
    }

    @Post()
    async createTemperatura(@Body() body: Temperatura): Promise<Temperatura> {
        return this.temperaturaService.createTemperatura(body);
    }
}
