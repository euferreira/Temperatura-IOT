import {Module} from "@nestjs/common";
import {TemperaturaService} from "./temperatura.service";
import {TemperaturaController} from "./temperatura.controller";
import {SequelizeModule} from "@nestjs/sequelize";
import {Temperatura} from "./temperatura.entity";

@Module({
    imports: [
        SequelizeModule.forFeature([
            Temperatura
        ]),
    ],
    controllers: [
        TemperaturaController
    ],
    providers: [
        TemperaturaService
    ],
})
export class TemperaturaModule {
}
