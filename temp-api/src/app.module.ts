import {Module} from '@nestjs/common';
import {AppController} from './app.controller';
import {AppService} from './app.service';
import {TemperaturaModule} from "./temperatura/temperatura.module";
import {ConfigModule} from '@nestjs/config';
import {SequelizeModule} from "@nestjs/sequelize";

@Module({
    imports: [
        ConfigModule.forRoot(),
        SequelizeModule.forRoot({
            dialect: 'mysql',
            host: process.env.DB_HOST,
            port: 3306,
            username: process.env.DB_USER,
            password: process.env.DB_PASS,
            database: process.env.DB_NAME,
            autoLoadModels: true,
            synchronize: true,
            timezone: '-03:00',
        }),
        TemperaturaModule,
    ],
    controllers: [AppController],
    providers: [
        AppService
    ],
})
export class AppModule {
}
