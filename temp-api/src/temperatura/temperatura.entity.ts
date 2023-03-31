import { Column, DataType, Model, Table } from "sequelize-typescript";
import { IsNotEmpty, IsNumber } from "class-validator";

@Table({
  tableName: "temperaturas"
})
export class Temperatura extends Model<Temperatura> {
  @IsNotEmpty()
  @IsNumber()
  @Column({
    type: DataType.DOUBLE,
    allowNull: false
  })
  temperatura: number;

  @IsNotEmpty()
  @IsNumber()
  @Column({
    type: DataType.DOUBLE,
    allowNull: false
  })
  umidade: number;
}
